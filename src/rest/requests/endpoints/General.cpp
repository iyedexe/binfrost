#include "rest/requests/endpoints/General.hpp"
#include "utils.hpp"

namespace BNB::REST::Endpoints::General
{
    Ping::Ping()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/ping";
    }
    http::request<http::dynamic_body> Ping::dump()
    {
        return RequestsBuilder::buildUnsignedRequest(method_, uri_);
    }

    Time::Time()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/time";
    }
    http::request<http::dynamic_body> Time::dump()
    {
        return RequestsBuilder::buildUnsignedRequest(method_, uri_);
    }

    ExchangeInfo::ExchangeInfo()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/exchangeInfo";

    }
    http::request<http::dynamic_body> ExchangeInfo::dump()
    {
        // Enforce Binance rules
        if (symbol_ && symbols_) {
            throw std::invalid_argument("exchangeInfo: 'symbol' and 'symbols' are mutually exclusive");
        }
        if (symbolStatus_ && (symbol_ || symbols_)) {
            throw std::invalid_argument("exchangeInfo: 'symbolStatus' cannot be used with 'symbol' or 'symbols'");
        }

        if (symbol_) {
            params_.emplace("symbol", *symbol_);
        }
        if (symbols_) {
            const std::string j = json_array(*symbols_);
            params_.emplace("symbols", j);
        }
        if (permissions_) {
            if (permissions_->size() == 1) {
                params_.emplace("permissions", permissions_->front());
            } else if (!permissions_->empty()) {
                const std::string j = json_array(*permissions_);
                params_.emplace("permissions", j);
            }
        }
        if (showPermissionSets_) {
            params_.emplace("showPermissionSets", *showPermissionSets_ ? "true" : "false");
        }
        if (symbolStatus_) {
            params_.emplace("symbolStatus", *symbolStatus_);
        }
        return RequestsBuilder::buildUnsignedRequest(method_, uri_, params_);
    }

}
