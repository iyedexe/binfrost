#include "fix/Feeder.hpp"
#include "logger.hpp"

namespace BNB::FIX
{
    void Feeder::onMessage(const FIX44::MD::Heartbeat& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Heartbeat: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::TestRequest& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled TestRequest: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::Reject& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Reject: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::Logout& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Logout: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::Logon& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Logon: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::LimitQuery& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled LimitQuery: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::LimitResponse& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled LimitResponse: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::InstrumentListRequest& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled InstrumentListRequest: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::InstrumentList& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled InstrumentList: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::MarketDataRequest& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataRequest: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::MarketDataRequestReject& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataRequestReject: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::MarketDataSnapshot& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataSnapshot: [{}]", replaceSOHWithPipe(message.toString()));
    }

    void Feeder::onMessage(const FIX44::MD::MarketDataIncrementalRefresh& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataIncrementalRefresh: [{}]", replaceSOHWithPipe(message.toString()));
    }
    void Feeder::onMessage(const FIX44::MD::News& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled News: [{}]", replaceSOHWithPipe(message.toString()));
    }

}
