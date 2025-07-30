#include "rest/requests/RequestsBuilder.hpp"
#include "logger.hpp"

namespace BNB::REST
{
    http::request<http::dynamic_body> RequestsBuilder::buildBasicRequest(http::verb method, const std::string& uri)
    {
        urls::url url;
        url.set_path(uri);
        http::request<http::dynamic_body> req{method, url.encoded_target(), 11};
        req.set(http::field::host, instance->endpoint_);
        req.set(http::field::user_agent, "Binance Client");
        return req;
    }

    http::request<http::dynamic_body> RequestsBuilder::buildRequest(http::verb method, const urls::url& url)
    {
 
        http::request<http::dynamic_body> req{method, url.encoded_target(), 11};
        req.set(http::field::user_agent, "Binance Client");
        req.set(http::field::host, instance->endpoint_);
        return req;
    }

    http::request<http::dynamic_body> RequestsBuilder::buildSignedRequest(http::verb method, urls::url& url)
    {
        
        std::string signature = instance->signatureKey_->sign(url.query());    
        auto qp = url.params();
        qp.append(urls::param_view{"signature", urls::string_view(signature)});

        http::request<http::dynamic_body> req{method, url.encoded_target(), 11};

        req.set(http::field::user_agent, "Binance Client");
        req.set(http::field::host, instance->endpoint_);
        req.set("X-MBX-APIKEY", instance->apiKey_);

        return req;
    }


    http::request<http::dynamic_body> RequestsBuilder::buildApiKeyRequest(http::verb method, const std::string& uri, const std::map<std::string, std::string>& params)
    {
        http::request<http::dynamic_body> req{method, uri, 11};
        req.set(http::field::host, instance->endpoint_);
        req.set(http::field::user_agent, "Binance Client");
        req.set("X-MBX-APIKEY", instance->apiKey_);

        for (auto& param : params) {
            req.set(param.first, param.second);
        }
        return req;
    }
}
