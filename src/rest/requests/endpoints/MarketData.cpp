#include "rest/requests/endpoints/MarketData.hpp"
#include "utils.hpp"

namespace BNB::REST::Endpoints::MarketData
{
    OrderBook::OrderBook()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/depth";
    }
    http::request<http::dynamic_body> OrderBook::dump() const
    {
        urls::url url;
        url.set_path(uri_);
        auto qp = url.params();

        qp.append(urls::param_view{"symbol", urls::string_view(symbol_)});
        if (limit_) {
            qp.append(urls::param_view{"limit", urls::string_view(std::to_string(*limit_))});
        }
        return RequestsBuilder::buildRequest(method_, url);
    }

    Trades::Trades()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/trades";
    }
    http::request<http::dynamic_body> Trades::dump() const
    {
        urls::url url;
        url.set_path(uri_);
        auto qp = url.params();

        qp.append(urls::param_view{"symbol", urls::string_view(symbol_)});
        if (limit_) {
            qp.append(urls::param_view{"limit", urls::string_view(std::to_string(*limit_))});
        }
        return RequestsBuilder::buildRequest(method_, url);
    }

    HistoricalTrades::HistoricalTrades()
    {
        method_ = http::verb::get;
        uri_ = "/api/v3/historicalTrades";
    }
    http::request<http::dynamic_body> HistoricalTrades::dump() const
    {
        urls::url url;
        url.set_path(uri_);
        auto qp = url.params();

        qp.append(urls::param_view{"symbol", urls::string_view(symbol_)});
        if (limit_) {
            qp.append(urls::param_view{"limit", urls::string_view(std::to_string(*limit_))});
        }
        if (fromId_) {
            qp.append(urls::param_view{"fromId", urls::string_view(std::to_string(*fromId_))});
        }
        return RequestsBuilder::buildRequest(method_, url);
    }

}
