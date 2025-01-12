#include "ws/requests/IRequests.hpp"
#include "ws/requests/RequestsBuilder.hpp"
#include "logger.hpp"

namespace BNB::WS::Trading
{
    class PlaceNewOrder : public IRequest
    {
    public:
        PlaceNewOrder();
        std::string dump() const override;
    };

    class TestNewOrder : public IRequest
    {
    public:
        TestNewOrder();
        std::string dump() const override;
    };

    class QueryOrder : public IRequest
    {
    public:
        QueryOrder();
        std::string dump() const override;
    };

    class CancelOrder : public IRequest
    {
    public:
        CancelOrder();
        std::string dump() const override;
    };

    class CancelAndReplaceOrder : public IRequest
    {
    public:
        CancelAndReplaceOrder();
        std::string dump() const override;
    };

    class CurrentOpenOrders : public IRequest
    {
    public:
        CurrentOpenOrders();
        std::string dump() const override;
    };

    class CancelOpenOrders : public IRequest
    {
    public:
        CancelOpenOrders();
        std::string dump() const override;
    };
}
    