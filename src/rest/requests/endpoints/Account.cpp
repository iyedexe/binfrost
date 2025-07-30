#include "rest/requests/endpoints/Account.hpp"
#include "utils.hpp"

namespace BNB::REST::Endpoints::Account
{
    AccountInformation::AccountInformation()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/account";

    }
    http::request<http::dynamic_body> AccountInformation::dump()
    {
        params_.emplace("timestamp", getTimestamp());
        if (omitZeroBalances_) {
            params_.emplace("omitZeroBalances", *omitZeroBalances_ ? "true" : "false");
        }
        if (recvWindow_) {
            params_.emplace("recvWindow", std::to_string(*recvWindow_));
        }
        return RequestsBuilder::buildSignedRequest(method_, uri_, params_);
    }

    QueryOrder::QueryOrder()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/order";

    }
    http::request<http::dynamic_body> QueryOrder::dump()
    {
        params_.emplace("symbol", symbol_);
        if (orderId_) {
            params_.emplace("recvWindow", std::to_string(*orderId_));
        }
        if (origClientOrderId_) {
            params_.emplace("recvWindow", *origClientOrderId_);
        }
        if (recvWindow_) {
            params_.emplace("recvWindow", std::to_string(*recvWindow_));
        }
        params_.emplace("timestamp", getTimestamp());

        return RequestsBuilder::buildSignedRequest(method_, uri_, params_);
    }

}
