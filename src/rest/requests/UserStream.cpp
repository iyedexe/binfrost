#include "rest/requests/UserStream.hpp"

namespace BNB::REST::UserStream
{
    Start::Start()
    {
        method_ = http::verb::post;
        uri_ = "/api/v3/userDataStream";
        params_ = {};
    }
    http::request<http::dynamic_body> Start::dump() const
    {
        return RequestsBuilder::buildApiKeyRequest(method_, uri_, params_);
    }

    KeepAlive::KeepAlive(const std::string& ListenKey)
    {
        method_ = http::verb::put;
        uri_ = "/api/v3/userDataStream";
        params_ = {{"listenKey", ListenKey}};
    }
    http::request<http::dynamic_body> KeepAlive::dump() const
    {
        return RequestsBuilder::buildApiKeyRequest(method_, uri_, params_);
    }

    Close::Close(const std::string& ListenKey)
    {
        method_ = http::verb::delete_;
        uri_ = "/api/v3/userDataStream";
        params_ = {{"listenKey", ListenKey}};

    }
    http::request<http::dynamic_body> Close::dump() const
    {
        return RequestsBuilder::buildApiKeyRequest(method_, uri_, params_);
    }

}
