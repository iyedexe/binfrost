#pragma once
#include "rest/requests/IRequest.hpp"
#include "rest/requests/RequestsBuilder.hpp"

namespace BNB::REST::Endpoints::Account
{
    class AccountInformation : public IRequest
    {
    public:
        AccountInformation();

        AccountInformation& omitZeroBalances(bool b) { omitZeroBalances_ = b; return *this; }
        AccountInformation& recvWindow(long l) { recvWindow_ = l; return *this; }
        AccountInformation& timestamp(long l) { timestamp_ = l; return *this; }

        http::request<http::dynamic_body> dump() const;
    private:
        long timestamp_;
        std::optional<int> omitZeroBalances_;
        std::optional<long> recvWindow_;
        
    };

}
