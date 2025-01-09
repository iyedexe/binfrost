#include "rest/ApiClient.hpp"
#include <iostream>

namespace BNB::REST
{
    ApiClient::ApiClient(const std::string& restEndpoint):
        host_(restEndpoint), ioc_(), resolver_(ioc_), ctx_{boost::asio::ssl::context::tls_client}
    {
        // ctx_.set_verify_mode(boost::asio::ssl::verify_peer); // Verify the certificate does not work same issue as websockets
        ctx_.set_default_verify_paths();
        ctx_.set_verify_mode(boost::asio::ssl::verify_none);
        ctx_.set_options(boost::asio::ssl::context::default_workarounds |
                        boost::asio::ssl::context::no_sslv2 |
                        boost::asio::ssl::context::no_sslv3 |
                        boost::asio::ssl::context::single_dh_use);

    }

    std::string ApiClient::sendRequest(const IRequest& request)
    {
        auto const results = resolver_.resolve(host_, "443");
        boost::beast::ssl_stream<boost::beast::tcp_stream> tls_stream{ioc_, ctx_};
        boost::beast::get_lowest_layer(tls_stream).connect(results);
        if (!SSL_set_tlsext_host_name(tls_stream.native_handle(), host_.c_str())) {
           throw boost::system::system_error(
            boost::asio::error::invalid_argument);
        }

        tls_stream.handshake(boost::asio::ssl::stream_base::client);

        http::write(tls_stream, request.dump());

        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(tls_stream, buffer, res);

        boost::system::error_code ec;
        tls_stream.shutdown(ec);
        // if (ec && ec != boost::asio::error::eof) {
        //     throw boost::system::system_error{ec};
        // }
        return beast::buffers_to_string(res.body().data());

    }
}