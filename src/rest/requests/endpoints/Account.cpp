#include "rest/requests/endpoints/Account.hpp"
#include "utils.hpp"

namespace BNB::REST::Endpoints::Account
{
    AccountInformation::AccountInformation()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/account";

    }
    http::request<http::dynamic_body> AccountInformation::dump() const
    {
        urls::url url;
        url.set_path(uri_);
        auto qp = url.params();

        qp.append(urls::param_view{"timestamp", urls::string_view(getTimestamp())});
        if (omitZeroBalances_) {
            qp.append(urls::param_view{"omitZeroBalances", urls::string_view(urls::string_view(*omitZeroBalances_ ? "true" : "false"))});
        }
        if (recvWindow_) {
            qp.append(urls::param_view{"recvWindow", urls::string_view(std::to_string(*recvWindow_))});
        }
        return RequestsBuilder::buildSignedRequest(method_, url);
    }

}
