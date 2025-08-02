#pragma once

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Message.h>
#include <quickfix/SessionID.h>
#include <quickfix/Field.h>
#include "crypto/ed25519.hpp"
#include "fix/MessageBuilder.hpp"

class FixApplication : public FIX::Application, public FIX::MessageCracker
{
public:
    FixApplication(const std::string &apiKey, crypto::ed25519 &key);
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
};
