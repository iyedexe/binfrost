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
using namespace FIX;

namespace BNB::FIX
{
    class Client
    {
    public:
        Client(const std::string &apiKey, crypto::ed25519 &key);
        void init();
        void sendMessage(IMessage &message);
        void onMessage(const Message &message, const SessionID &sessionID);
        void connect();
        void disconnect();
        void waitUntilConnected();

    private:
        SessionSettings buildSettings();
        virtual std::string getEndpoint() = 0;
        virtual std::string getPort() = 0;
        virtual std::string getSenderCompID() = 0;
        virtual std::string getDictionnaryPath() = 0;


        FixApplication application;
        SessionSettings settings;

        std::unique_ptr<FileStoreFactory> storeFactory;
        std::unique_ptr<FileLogFactory> logFactory;
        std::unique_ptr<SSLSocketInitiator> initiator;
    };
}
