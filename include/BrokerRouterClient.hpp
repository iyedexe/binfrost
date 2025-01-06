#include <fix8/f8config.h>
#include <fix8/f8includes.hpp>      // Core FIX8 includes
#include <fix8/f8types.hpp>         // Core FIX8 types
#include <fix8/usage.hpp>           // For session usage utilities
#include "bnb/oe/broker_router.hpp"
#include "bnb/oe/broker_types.hpp"
#include "bnb/oe/broker_classes.hpp"
#include "utils.hpp"


namespace FIX
{
    namespace BNB
    {
        class BrokerSessionClient;

        class BrokerRouterClient : public FIX8::BNB::broker_Router
        {
        BrokerSessionClient& _session; 

        public:
        BrokerRouterClient(BrokerSessionClient& session) : _session(session) {}
        virtual ~BrokerRouterClient() {}

        // Override these methods to receive specific message callbacks.
        bool operator() (const FIX8::BNB::Heartbeat *msg) const;
        bool operator() (const FIX8::BNB::Logon *msg) const;
        bool operator() (const FIX8::BNB::Logout *msg) const;
        bool operator() (const FIX8::BNB::TestRequest *msg) const;
        bool operator() (const FIX8::BNB::Reject *msg) const;
        bool operator() (const FIX8::BNB::ExecutionReport *msg) const;
        bool operator() (const FIX8::BNB::OrderCancelReject *msg) const;
        // bool operator() (const FIX8::BNB::News *msg) const;
        // bool operator() (const FIX8::BNB::NewOrderSingle *msg) const;
        // bool operator() (const FIX8::BNB::NewOrderList *msg) const;
        // bool operator() (const FIX8::BNB::OrderCancelRequest *msg) const;
        // bool operator() (const FIX8::BNB::ListStatus *msg) const;
        // bool operator() (const FIX8::BNB::OrderCancelRequestAndNewOrderSingle *msg) const;
        // bool operator() (const FIX8::BNB::LimitQuery *msg) const;
        // bool operator() (const FIX8::BNB::LimitResponse *msg) const;
        // bool operator() (const FIX8::BNB::OrderMassCancelRequest *msg) const;
        // bool operator() (const FIX8::BNB::OrderMassCancelReport *msg) const;
        };    
    }
}