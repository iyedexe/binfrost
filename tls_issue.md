
exception: Certificate validation error: Unacceptable certificate from 54.64.178.180: application verification failure


X509_V_ERR_APPLICATION_VERIFICATION: application verification failure
An application specific error. 
This will never be returned unless explicitly set by an application callback.

SecureStreamSocket->connect is called

void SecureSocketImpl::connect(const SocketAddress& address, const Poco::Timespan& timeout, bool performHandshake)
{
	if (_pSSL) reset();

	poco_assert (!_pSSL);

	_pSocket->connect(address, timeout);
	Poco::Timespan receiveTimeout = _pSocket->getReceiveTimeout();
	Poco::Timespan sendTimeout = _pSocket->getSendTimeout();
	_pSocket->setReceiveTimeout(timeout);
	_pSocket->setSendTimeout(timeout);

	connectSSL(performHandshake);
	
	_pSocket->setReceiveTimeout(receiveTimeout);
	_pSocket->setSendTimeout(sendTimeout);
}

oid SecureSocketImpl::connectSSL(bool performHandshake)
{
	poco_assert (!_pSSL);
	poco_assert (_pSocket->initialized());

	LockT l(_mutex);

	::BIO* pBIO = ::BIO_new(BIO_s_socket());
	if (!pBIO) throw SSLException("Cannot create SSL BIO object");
	BIO_set_fd(pBIO, static_cast<int>(_pSocket->sockfd()), BIO_NOCLOSE);

	_pSSL = ::SSL_new(_pContext->sslContext());
	if (!_pSSL)
	{
		::BIO_free(pBIO);
		throw SSLException("Cannot create SSL object");
	}
	::SSL_set_bio(_pSSL, pBIO, pBIO);
	::SSL_set_ex_data(_pSSL, SSLManager::instance().socketIndex(), this);

	if (!_peerHostName.empty())
	{
		SSL_set_tlsext_host_name(_pSSL, _peerHostName.c_str());
	}

#if OPENSSL_VERSION_NUMBER >= 0x10001000L
	if(_pContext->ocspStaplingResponseVerificationEnabled())
	{
		SSL_set_tlsext_status_type(_pSSL, TLSEXT_STATUSTYPE_ocsp);
	}
#endif

	if (_pSession && _pSession->isResumable())
	{
		::SSL_set_session(_pSSL, _pSession->sslSession());
	}

	try
	{
		if (performHandshake && _pSocket->getBlocking())
		{
			int ret = ::SSL_connect(_pSSL);
			handleError(ret);
			verifyPeerCertificate();
		}
		else
		{
			::SSL_set_connect_state(_pSSL);
			_needHandshake = true;
		}
	}
	catch (...)
	{
		::SSL_free(_pSSL);
		_pSSL = nullptr;
		throw;
	}
}

void SecureSocketImpl::verifyPeerCertificate(const std::string& hostName)
{
	long certErr = verifyPeerCertificateImpl(hostName);
	if (certErr != X509_V_OK)
	{
		std::string msg = Utility::convertCertificateError(certErr);
		throw CertificateValidationException("Unacceptable certificate from " + hostName, msg);
	}
}


long SecureSocketImpl::verifyPeerCertificateImpl(const std::string& hostName)
{
	Context::VerificationMode mode = _pContext->verificationMode();
	if (mode == Context::VERIFY_NONE || !_pContext->extendedCertificateVerificationEnabled() ||
	   (mode != Context::VERIFY_STRICT && isLocalHost(hostName)))
	{
		return X509_V_OK;
	}

	::X509* pCert = ::SSL_get_peer_certificate(_pSSL);
	if (pCert)
	{
		X509Certificate cert(pCert);
		return cert.verify(hostName) ? X509_V_OK : X509_V_ERR_APPLICATION_VERIFICATION;
	}
	else return X509_V_OK;
}




bool X509Certificate::verify(const Poco::Crypto::X509Certificate& certificate, const std::string& hostName)
{
	if (X509_check_host(const_cast<X509*>(certificate.certificate()), hostName.c_str(), hostName.length(), 0, NULL) == 1)
	{
		return true;
	}
	else
	{
		IPAddress ip;
		if (IPAddress::tryParse(hostName, ip))
		{
		    return (X509_check_ip_asc(const_cast<X509*>(certificate.certificate()), hostName.c_str(), 0) == 1);
		}
	}
	return false;
}



https://docs.openssl.org/1.1.1/man3/X509_check_host/#synopsis

Checks the IP vs the CN which is a regex for the hostname