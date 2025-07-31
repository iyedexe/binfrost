#pragma once
#include "rest/requests/IRequest.hpp"
#include "rest/requests/RequestsBuilder.hpp"

namespace BNB::REST::Endpoints::General
{
    class Ping : public IRequest
    {
    public:
        Ping();
        http::request<http::dynamic_body> dump();
    };
    class Time : public IRequest
    {
    public:
        Time();
        http::request<http::dynamic_body> dump();
    };
    class ExchangeInfo : public IRequest
    {
    public:
        ExchangeInfo();

        ExchangeInfo &&symbol(std::string s)
        {
            symbol_ = std::move(s);
            return std::move(*this);
        }
        ExchangeInfo &&symbols(std::vector<std::string> v)
        {
            symbols_ = std::move(v);
            return std::move(*this);
        }
        ExchangeInfo &&permissions(std::vector<std::string> v)
        {
            permissions_ = std::move(v);
            return std::move(*this);
        }
        ExchangeInfo &&showPermissionSets(bool v)
        {
            showPermissionSets_ = v;
            return std::move(*this);
        }
        ExchangeInfo &&symbolStatus(std::string v)
        {
            symbolStatus_ = std::move(v);
            return std::move(*this);
        }

        http::request<http::dynamic_body> dump();

    private:
        std::optional<std::string> symbol_;
        std::optional<std::vector<std::string>> symbols_;
        std::optional<std::vector<std::string>> permissions_;
        std::optional<bool> showPermissionSets_; // defaults to true on server; only send if you want false
        std::optional<std::string> symbolStatus_;
    };

}
