#include "fix/Client.hpp"
#include "codegen/fix/OE/fix44/ExecutionReport.hpp"
#include "codegen/fix/OE/fix44/Heartbeat.hpp"
#include "codegen/fix/OE/fix44/LimitQuery.hpp"
#include "codegen/fix/OE/fix44/LimitResponse.hpp"
#include "codegen/fix/OE/fix44/ListStatus.hpp"
#include "codegen/fix/OE/fix44/Logon.hpp"
#include "codegen/fix/OE/fix44/Logout.hpp"
#include "codegen/fix/OE/fix44/NewOrderList.hpp"
#include "codegen/fix/OE/fix44/NewOrderSingle.hpp"
#include "codegen/fix/OE/fix44/News.hpp"
#include "codegen/fix/OE/fix44/OrderAmendKeepPriorityRequest.hpp"
#include "codegen/fix/OE/fix44/OrderAmendReject.hpp"
#include "codegen/fix/OE/fix44/OrderCancelReject.hpp"
#include "codegen/fix/OE/fix44/OrderCancelRequest.hpp"
#include "codegen/fix/OE/fix44/OrderCancelRequestAndNewOrderSingle.hpp"
#include "codegen/fix/OE/fix44/OrderMassCancelReport.hpp"
#include "codegen/fix/OE/fix44/OrderMassCancelRequest.hpp"

#include "codegen/fix/OE/fix44/MessageCracker.hpp"

namespace BNB::FIX
{
    class Broker : public Client, public FIX44::OE::MessageCracker
    {
    public:
        Broker(const std::string &apiKey, crypto::ed25519 &key)
            : Client(apiKey, key)
        {
            init();
        }
        void onMessage(const Message &message, const SessionID &sessionID) { crack(message, sessionID); }
        virtual void onMessage(const FIX44::OE::ExecutionReport &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::Heartbeat &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::LimitQuery &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::LimitResponse &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::ListStatus &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::Logon &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::Logout &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::NewOrderList &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::NewOrderSingle &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::News &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderAmendKeepPriorityRequest &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderAmendReject &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderCancelReject &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderCancelRequest &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderCancelRequestAndNewOrderSingle &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderMassCancelReport &message, const SessionID &sessionID) override;
        virtual void onMessage(const FIX44::OE::OrderMassCancelRequest &message, const SessionID &sessionID) override;

    private:
        virtual std::string getEndpoint() { return "fix-oe.testnet.binance.vision"; }
        virtual std::string getPort() { return "9000"; }
        virtual std::string getSenderCompID() { return "BROKER"; }
        virtual std::string getDictionnaryPath() { return "../include/codegen/fix/OE/FIX44.xml"; }
    };
}
