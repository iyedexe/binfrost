#pragma once
#include "rest/requests/IRequest.hpp"
#include "rest/requests/RequestsBuilder.hpp"

namespace BNB::REST::Endpoints::Account
{
    class AccountInformation : public IRequest
    {
    public:
        AccountInformation();

        AccountInformation &&omitZeroBalances(bool b)
        {
            omitZeroBalances_ = b;
            return std::move(*this);
        }
        AccountInformation &&recvWindow(long l)
        {
            recvWindow_ = l;
            return std::move(*this);
        }
        AccountInformation &&timestamp(long l)
        {
            timestamp_ = l;
            return std::move(*this);
        }

        http::request<http::dynamic_body> dump();

    private:
        long timestamp_;
        std::optional<int> omitZeroBalances_;
        std::optional<long> recvWindow_;
    };

    class QueryOrder : public IRequest
    {
    public:
        QueryOrder();

        QueryOrder &&symbol(const std::string &s)
        {
            symbol_ = s;
            return std::move(*this);
        }
        QueryOrder &&orderId(long l)
        {
            orderId_ = l;
            return std::move(*this);
        }
        QueryOrder &&origClientOrderId(const std::string &s)
        {
            origClientOrderId_ = s;
            return std::move(*this);
        }
        QueryOrder &&recvWindow(long l)
        {
            recvWindow_ = l;
            return std::move(*this);
        }
        QueryOrder &&timestamp(long l)
        {
            timestamp_ = l;
            return std::move(*this);
        }

        http::request<http::dynamic_body> dump();

    private:
        std::string symbol_;
        std::optional<long> orderId_;
        std::optional<std::string> origClientOrderId_;
        std::optional<long> recvWindow_;
        long timestamp_;
    };

}
