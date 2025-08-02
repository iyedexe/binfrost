#include "fix/FixApplication.hpp"
#include "utils.hpp"
#include "logger.hpp"

FixApplication::FixApplication(const std::string &apiKey, crypto::ed25519 &key) : msgBuilder_(apiKey, key)
{
}

void FixApplication::onCreate(const FIX::SessionID &sessionID)
{
    LOG_INFO("Session created: {}", sessionID.toString());
}

void FixApplication::onLogon(const FIX::SessionID &sessionID)
{
    LOG_INFO("Logon: {}", sessionID.toString());
}

void FixApplication::onLogout(const FIX::SessionID &sessionID)
{
    LOG_INFO("Logout: {}", sessionID.toString());
}

void FixApplication::toAdmin(FIX::Message &message, const FIX::SessionID &sessionID)
{
    auto const &msgType = message.getHeader().getField(FIX::FIELD::MsgType);

    if (msgType == "A")
    {
        LOG_INFO("Building logon message");
        msgBuilder_.fillLogon(message);
        LOG_INFO("Sending Admin: {}", message.toString());
    }
}

void FixApplication::fromAdmin(const FIX::Message &message, const FIX::SessionID &sessionID)
    QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon)
{
    LOG_INFO("Received Admin: {}", message.toString());
}

void FixApplication::toApp(FIX::Message &message, const FIX::SessionID &sessionID)
    QUICKFIX_THROW(FIX::DoNotSend)
{
    LOG_INFO("Sending App: {}", message.toString());
}
void FixApplication::fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
    QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType)
{
    crack(message, sessionID);
}
