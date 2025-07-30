#pragma once
#include "rest/requests/IRequest.hpp"
#include "rest/requests/RequestsBuilder.hpp"

namespace BNB::REST::UserStream // Deprecated
{
    class Start : public IRequest
    {
    public:
        Start();
        http::request<http::dynamic_body> dump();
    };
    class KeepAlive : public IRequest
    {
    public:
        KeepAlive(const std::string& ListenKey);
        http::request<http::dynamic_body> dump();
    };
    class Close : public IRequest
    {
    public:
        Close(const std::string& ListenKey);
        http::request<http::dynamic_body> dump();
    };

}
