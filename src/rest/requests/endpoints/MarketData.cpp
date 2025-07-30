#include "rest/requests/endpoints/MarketData.hpp"
#include "utils.hpp"

namespace BNB::REST::Endpoints::MarketData
{
    OrderBook::OrderBook()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/depth";
    }
    http::request<http::dynamic_body> OrderBook::dump()
    {
        params_.emplace("symbol", symbol_);
        if (limit_) {
            params_.emplace("limit", std::to_string(*limit_));
        }
        return RequestsBuilder::buildUnsignedRequest(method_, uri_, params_);
    }

    Trades::Trades()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/trades";
    }
    http::request<http::dynamic_body> Trades::dump()
    {
        params_.emplace("symbol", symbol_);
        if (limit_) {
            params_.emplace("limit", std::to_string(*limit_));
        }
        return RequestsBuilder::buildUnsignedRequest(method_, uri_, params_);
    }

    HistoricalTrades::HistoricalTrades()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/historicalTrades";
    }
    http::request<http::dynamic_body> HistoricalTrades::dump()
    {
        params_.emplace("symbol", symbol_);
        if (limit_) {
            params_.emplace("limit", std::to_string(*limit_));
        }
        if (fromId_) {
            params_.emplace("fromId", std::to_string(*fromId_));
        }
        return RequestsBuilder::buildUnsignedRequest(method_, uri_, params_);
    }

}
