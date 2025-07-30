#include "rest/requests/RequestsBuilder.hpp"
#include "logger.hpp"

namespace BNB::REST
{
    http::request<http::dynamic_body> RequestsBuilder::buildUnsignedRequest(http::verb method, const std::string& uri, const std::map<std::string, std::string>& params)
    {
        urls::url url;
        url.set_path(uri);
        if (params.size() > 0)
        {
            auto qp = url.params();
            for (const auto& pair : params) {
                qp.append(urls::param_view{pair.first, urls::string_view(pair.second)});
            }
        }
        http::request<http::dynamic_body> req{method, url.encoded_target(), 11};
        req.set(http::field::host, instance->endpoint_);
        req.set(http::field::user_agent, "Binance Client");
        return req;
    }

    http::request<http::dynamic_body> RequestsBuilder::buildSignedRequest(http::verb method, const std::string& uri, const std::map<std::string, std::string>& params)
    {
        urls::url url;
        url.set_path(uri);
        if (params.size() > 0)
        {
            auto qp = url.params();
            for (const auto& pair : params) {
                qp.append(urls::param_view{pair.first, urls::string_view(pair.second)});
            }
        }
        std::string signature = instance->signatureKey_->sign(url.query());    
        auto qp = url.params();
        qp.append(urls::param_view{"signature", urls::string_view(signature)});

        http::request<http::dynamic_body> req{method, url.encoded_target(), 11};

        req.set(http::field::user_agent, "Binance Client");
        req.set(http::field::host, instance->endpoint_);
        req.set("X-MBX-APIKEY", instance->apiKey_);

        return req;
    }

}
