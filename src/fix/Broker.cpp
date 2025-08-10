#include "fix/Broker.hpp"
#include "logger.hpp"

namespace BNB::FIX
{
    void Broker::onMessage(const FIX44::OE::ExecutionReport &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled ExecutionReport: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::Heartbeat &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled Heartbeat: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::LimitQuery &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled LimitQuery: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::LimitResponse &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled LimitResponse: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::ListStatus &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled ListStatus: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::Logon &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled Logon: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::Logout &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled Logout: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::NewOrderList &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled NewOrderList: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::NewOrderSingle &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled NewOrderSingle: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::News &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled News: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderAmendKeepPriorityRequest &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderAmendKeepPriorityRequest: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderAmendReject &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderAmendReject: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderCancelReject &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderCancelReject: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderCancelRequest &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderCancelRequest: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderCancelRequestAndNewOrderSingle &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderCancelRequestAndNewOrderSingle: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderMassCancelReport &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderMassCancelReport: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Broker::onMessage(const FIX44::OE::OrderMassCancelRequest &message, const SessionID &sessionID)
    {
        LOG_WARNING("Received unhandled OrderMassCancelRequest: [{}]", replaceSOHWithPipe(message.toString()));
    }

}
