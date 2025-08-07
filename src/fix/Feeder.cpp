#include "fix/Feeder.hpp"
#include "logger.hpp"

namespace BNB::FIX
{
/*    void Feeder::onMessage(const FIX44::feeder::Heartbeat& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Heartbeat: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::TestRequest& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled TestRequest: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::Reject& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Reject: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::Logout& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Logout: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::Logon& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Logon: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::LimitQuery& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled LimitQuery: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::LimitResponse& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled LimitResponse: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::InstrumentListRequest& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled InstrumentListRequest: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::InstrumentList& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled InstrumentList: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::MarketDataRequest& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataRequest: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::MarketDataRequestReject& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataRequestReject: [{}]", replaceSOHWithPipe(message.toString()))
    }
*/
    void Feeder::onMessage(const Message &message, const SessionID &sessionID)
    {
        crack(message, sessionID);
    }

    void Feeder::onMessage(const FIX44::MD::MarketDataSnapshot& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataSnapshot: [{}]", replaceSOHWithPipe(message.toString()));
    }
/*
    void Feeder::onMessage(const FIX44::feeder::MarketDataIncrementalRefresh& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled MarketDataIncrementalRefresh: [{}]", replaceSOHWithPipe(message.toString()))
    }
    void Feeder::onMessage(const FIX44::feeder::News& message, const FIX::SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled News: [{}]", replaceSOHWithPipe(message.toString()))
    }
*/
}
