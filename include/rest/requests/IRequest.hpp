#pragma once
#include <string>
#include <map>
#include <boost/beast.hpp>

namespace http = boost::beast::http;

namespace BNB::REST
{
    class IRequest
    {
    public:
        IRequest() {
            // id_ = generateRequestId();
        }
        virtual ~IRequest() = default;
        // virtual std::string getId() const { return "id_"; }
        virtual http::verb getMethod() const { return method_; }
        virtual std::map<std::string, std::string> getParams() const { return params_; }
        virtual http::request<http::dynamic_body> dump() const = 0;
    protected:
        http::verb method_;
        std::string uri_;
        std::map<std::string, std::string> params_;
    };
}
