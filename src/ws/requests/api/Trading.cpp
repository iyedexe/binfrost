#include "ws/requests/api/Trading.hpp"

namespace BNB::WS::Trading
{
    PlaceNewOrder::PlaceNewOrder()
    {
        method_ = "order.place";
    }

    std::string PlaceNewOrder::dump() const {        
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }

    TestNewOrder::TestNewOrder()
    {
        method_ = "order.test";
    }
    std::string TestNewOrder::dump() const 
    {
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }
    
    QueryOrder::QueryOrder()
    {
        method_ = "order.status";
    }
    std::string QueryOrder::dump() const 
    {
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }

    CancelOrder::CancelOrder()
    {
        method_ = "order.cancel";
    }
    std::string CancelOrder::dump() const 
    {
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }

    CancelAndReplaceOrder::CancelAndReplaceOrder()
    {
        method_ = "order.cancelReplace";
    }
    std::string CancelAndReplaceOrder::dump() const 
    {
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }

    CurrentOpenOrders::CurrentOpenOrders()
    {
        method_ = "openOrders.status";        
    }
    std::string CurrentOpenOrders::dump() const 
    {
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }

    CancelOpenOrders::CancelOpenOrders()
    {
        method_ = "openOrders.cancelAll";
    }
    std::string CancelOpenOrders::dump() const 
    {
        return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
    }
}
    