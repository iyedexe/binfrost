#include "rest/requests/RequestsBuilder.hpp"
#include "logger.hpp"

namespace BNB::REST
{
    http::request<http::dynamic_body> RequestsBuilder::buildBasicRequest(http::verb method, const std::string& uri, const std::map<std::string, std::string>& params)
    {
        http::request<http::dynamic_body> req{method, uri, 11};
        for (auto& param : params) {
            req.set(param.first, param.second);
        }
        return req;
    }

    http::request<http::dynamic_body> RequestsBuilder::buildApiKeyRequest(http::verb method, const std::string& target, const std::map<std::string, std::string>& params)
    {
        http::request<http::dynamic_body> req{method, target, 11};
        req.set(http::field::host, "api.binance.com");
        req.set(http::field::user_agent, "Binance Client");
        req.set("X-MBX-APIKEY", instance->apiKey_);

        for (auto& param : params) {
            req.set(param.first, param.second);
        }
        return req;
    }
}
