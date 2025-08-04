#include "fix/FixApplication.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include "fix/FixClient.hpp"

FixApplication::FixApplication(const std::string &apiKey, crypto::ed25519 &key) : msgBuilder_(apiKey, key)
{
}

void FixApplication::setClient(FixClient* client) {
    client_ = client;
}

void FixApplication::onCreate(const FIX::SessionID& sessionID)
{
    LOG_INFO("Session created: {}", sessionID.toString());
    // Optional: store sessionID if needed
}

void FixApplication::onLogon(const FIX::SessionID &sessionID)
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        loggedOn_ = true;
    }
    cv_.notify_all();
    LOG_INFO("Logon: {}", sessionID.toString());
}

void FixApplication::onLogout(const FIX::SessionID &sessionID)
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        loggedOn_ = false;
    }
    LOG_INFO("Logout: {}", sessionID.toString());
}

bool FixApplication::isLoggedOn()
{
    return loggedOn_;
}

void FixApplication::waitForLogon()
{
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [this] { return loggedOn_.load(); });
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
    if (client_) {
        client_->onMessage();
    }

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
    LOG_INFO("Received App: {}", message.toString());

    if (client_) {
        client_->onMessage();
    }
}
