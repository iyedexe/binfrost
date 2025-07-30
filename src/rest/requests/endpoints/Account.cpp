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

}
