#pragma once
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Message.h>
#include <quickfix/SessionID.h>
#include <quickfix/Field.h>

#include "crypto/ed25519.hpp"
#include "fix/MessageBuilder.hpp"

class FixClient;  // Forward declaration
class FixApplication : public FIX::Application, public FIX::MessageCracker
{
public:
    FixApplication(const std::string &apiKey, crypto::ed25519 &key);
    void setClient(FixClient* client);
    bool isLoggedOn();
    void waitForLogon();

    void onCreate(const FIX::SessionID &sessionID) override;
    void onLogon(const FIX::SessionID &sessionID) override;
    void onLogout(const FIX::SessionID &sessionID) override;

    void toAdmin(FIX::Message &message, const FIX::SessionID &sessionID) override;
    void fromAdmin(const FIX::Message &message, const FIX::SessionID &sessionID)
        QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) override;
    void toApp(FIX::Message &message, const FIX::SessionID &sessionID)
        QUICKFIX_THROW(FIX::DoNotSend) override;
    void fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
        QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) override;

    void onMessage(const FIX44::ExecutionReport&, const FIX::SessionID&) override;
    void onMessage(const FIX44::OrderCancelReject&, const FIX::SessionID&) override;
        
private:
    MessageBuilder msgBuilder_;
    FixClient* client_ = nullptr;  // <-- store pointer

    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> loggedOn_ = false;
};
