#pragma once
#include <string>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "rest/requests/IRequest.hpp"


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace BNB::REST
{
    class ApiClient
    {
    public:
        ApiClient(const std::string& restEndpoint);
        ~ApiClient() = default;

        std::string sendRequest(const IRequest& request);
    private:
        std::string host_;
        net::io_context ioc_;
        tcp::resolver resolver_;
        net::ssl::context ctx_;
    };
}