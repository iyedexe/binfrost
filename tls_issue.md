
exception: Certificate validation error: Unacceptable certificate from 54.64.178.180: application verification failure


X509_V_ERR_APPLICATION_VERIFICATION: application verification failure
An application specific error. 
This will never be returned unless explicitly set by an application callback.

SecureStreamSocket->connect is called


Connection with TLS to Binance endpoint unsuccessfull due to certificate checking.
The adress checked against the host in the certificate is IP vs hostname in certificate which causes failure

Fix ideas : 
Secure socket method : 
	void setPeerHostName(const std::string& hostName);
		/// Sets the peer's host name used for certificate validation.

can be called from the sessionwrapper.hpp
_sock->setPeerHostName(from_or_default(_ses, "ip", ip));

Or class derived from FIX8::ClientSession<BNB::FIX::BrokerSessionClient> that sets this value

Detailed call stack :
<fix8::connection.cpp:338>
```
bool ClientConnection::connect()
{
	unsigned attempts(0);
	const LoginParameters& lparam(_session.get_login_parameters());
	const Poco::Timespan timeout(lparam._connect_timeout, 0);

	while (attempts < (lparam._reliable ? 1 : lparam._login_retries))
	{
		try
		{
			if (_addr == Poco::Net::SocketAddress())
				throw Poco::Net::InvalidAddressException("empty address");

			scout_info << "Trying to connect to: " << _addr.toString() << " (" << ++attempts << ')' << ( _secured ? " secured" : " not-secured");
>>>			_sock->connect(_addr, timeout);
			if (lparam._recv_buf_sz)
				set_recv_buf_sz(lparam._recv_buf_sz);
			if (lparam._send_buf_sz)
				set_send_buf_sz(lparam._send_buf_sz);
			_sock->setLinger(false, 0);
			_sock->setNoDelay(_no_delay);
			scout_info << "Connection successful";
			return _connected = true;
		}
		catch (Poco::Exception& e)
		{
			if (lparam._reliable)
			{
				scout_debug << "rethrowing Poco::Exception: " << e.displayText();
				throw;
			}
			scout_error << "exception: " << e.displayText();
			hypersleep<h_milliseconds>(lparam._login_retry_interval);
		}
		catch (exception& e)
		{
			if (lparam._reliable)
			{
				scout_debug << "rethrowing exception: " << e.what();
				throw;
			}
			scout_error << "exception: " << e.what();
			hypersleep<h_milliseconds>(lparam._login_retry_interval);
		}
	}
}
```
<POCO::SecureStreamSocketImpl.cpp:72>
```
void SecureStreamSocketImpl::connect(const SocketAddress& address, const Poco::Timespan& timeout)
{
	_impl.connect(address, timeout, !_lazyHandshake);
	reset(_impl.sockfd());
}
```

<POCO::SecureSocketImpl.cpp:128>
```
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
```

Socket is instanciated at : <fix8::sessionwrapper.hpp:232>
```
#ifdef FIX8_HAVE_OPENSSL
			bool secured(_ssl.is_secure());
			_sock = secured
				? new Poco::Net::SecureStreamSocket(_ssl._context)
				: new Poco::Net::StreamSocket;
```


<POCO::SecureSocketImpl.cpp:156>
```
void SecureSocketImpl::connectSSL(bool performHandshake)
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
```


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