#pragma once
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <quickfix/Application.h>
#include <quickfix/Message.h>
#include <quickfix/SessionID.h>
#include <quickfix/Field.h>

#include "crypto/ed25519.hpp"
#include "fix/MessageBuilder.hpp"

namespace BNB::FIX
{
    class Client;

}
class FixApplication : public FIX::Application
{
public:
    FixApplication(const std::string &apiKey, crypto::ed25519 &key);
    void setClient(BNB::FIX::Client* client);
    bool isLoggedOn();
    void waitForLogon();
    FIX::SessionID getSessionId() {return sessionId_;}
    

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
        
private:
    MessageBuilder msgBuilder_;
    BNB::FIX::Client* client_ = nullptr;
    FIX::SessionID sessionId_;

    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> loggedOn_ = false;
};
