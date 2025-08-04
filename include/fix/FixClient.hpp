#pragma once
#define HAVE_SSL 1

#include <map>
#include <string>

#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SSLSocketInitiator.h>
#include <quickfix/Session.h>
#include <quickfix/FixFields.h>

#include "fix/FixApplication.hpp"
#include "fix/messages/IMessage.hpp"

class FixClient
{
public:
    FixClient(const std::string &apiKey, crypto::ed25519 &key);
    void sendMessage(IMessage &message);
    void onMessage();
    void connect();
    void disconnect();
    void waitUntilConnected();
private:
    static FIX::SessionSettings buildSettings();

    FixApplication application;
    FIX::SessionSettings settings;
    FIX::FileStoreFactory storeFactory;
    FIX::FileLogFactory logFactory;
    FIX::SSLSocketInitiator initiator;
};