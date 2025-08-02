#pragma once
#define HAVE_SSL 1

#include "FixApplication.hpp"
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SSLSocketInitiator.h>
#include <map>
#include <string>

class FixClient
{
public:
    FixClient(const std::string &apiKey, crypto::ed25519 &key);
    void connect();
    void disconnect();

private:
    static FIX::SessionSettings buildSettings();

    FixApplication application;
    FIX::SessionSettings settings;
    FIX::FileStoreFactory storeFactory;
    FIX::FileLogFactory logFactory;
    FIX::SSLSocketInitiator initiator;
};