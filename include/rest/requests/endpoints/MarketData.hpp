#pragma once
#include "rest/requests/IRequest.hpp"
#include "rest/requests/RequestsBuilder.hpp"

namespace BNB::REST::Endpoints::MarketData
{
    class OrderBook : public IRequest
    {
    public:
        OrderBook();

        OrderBook&& symbol(std::string s) { symbol_ = std::move(s); return std::move(*this); }
        OrderBook&& limit(int l) { limit_ = l; return std::move(*this); }

        http::request<http::dynamic_body> dump();
    private:
        std::string symbol_;
        std::optional<int> limit_;
        
    };

    class Trades : public IRequest
    {
    public:
        Trades();

        Trades&& symbol(std::string s) { symbol_ = std::move(s); return std::move(*this); }
        Trades&& limit(int l) { limit_ = l; return std::move(*this); }

        http::request<http::dynamic_body> dump();
    private:
        std::string symbol_;
        std::optional<int> limit_;
        
    };

    class HistoricalTrades : public IRequest
    {
    public:
        HistoricalTrades();

        HistoricalTrades&& symbol(std::string s) { symbol_ = std::move(s); return std::move(*this); }
        HistoricalTrades&& limit(int l) { limit_ = l; return std::move(*this); }
        HistoricalTrades&& fromId(long l) { fromId_ = l; return std::move(*this); }
        
        http::request<http::dynamic_body> dump();
    private:
        std::string symbol_;
        std::optional<int> limit_;
        std::optional<long> fromId_;
        
    };

}
