#include "rest/requests/endpoints/General.hpp"
#include "utils.hpp"

namespace BNB::REST::Endpoints::General
{
    Ping::Ping()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/ping";
    }
    http::request<http::dynamic_body> Ping::dump() const
    {
        return RequestsBuilder::buildBasicRequest(method_, uri_);
    }

    Time::Time()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/time";
    }
    http::request<http::dynamic_body> Time::dump() const
    {
        return RequestsBuilder::buildBasicRequest(method_, uri_);
    }

    ExchangeInfo::ExchangeInfo()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/exchangeInfo";

    }
    http::request<http::dynamic_body> ExchangeInfo::dump() const
    {
        // Enforce Binance rules
        if (symbol_ && symbols_) {
            throw std::invalid_argument("exchangeInfo: 'symbol' and 'symbols' are mutually exclusive");
        }
        if (symbolStatus_ && (symbol_ || symbols_)) {
            throw std::invalid_argument("exchangeInfo: 'symbolStatus' cannot be used with 'symbol' or 'symbols'");
        }

        urls::url url;
        url.set_path(uri_);
        auto qp = url.params();

        if (symbol_) {
            qp.append(urls::param_view{"symbol", urls::string_view(*symbol_)});
        }
        if (symbols_) {
            const std::string j = json_array(*symbols_);
            qp.append(urls::param_view{"symbols", urls::string_view(j)});
        }
        if (permissions_) {
            if (permissions_->size() == 1) {
                qp.append(urls::param_view{"permissions",
                                           urls::string_view(permissions_->front())});
            } else if (!permissions_->empty()) {
                const std::string j = json_array(*permissions_);
                qp.append(urls::param_view{"permissions", urls::string_view(j)});
            }
        }
        if (showPermissionSets_) {
            qp.append(urls::param_view{"showPermissionSets",
                                       urls::string_view(*showPermissionSets_ ? "true" : "false")});
        }
        if (symbolStatus_) {
            qp.append(urls::param_view{"symbolStatus", urls::string_view(*symbolStatus_)});
        }
        return RequestsBuilder::buildRequest(method_, url);
    }

}
