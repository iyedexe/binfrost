#include <sstream>
#include <iostream>
#include "fix/Client.hpp"
#include "utils.hpp"
#include "logger.hpp"

namespace BNB::FIX
{
    Client::Client(const std::string &apiKey, crypto::ed25519 &key)
        : application(apiKey, key)
    {
        application.setClient(this);
    }

    void Client::init() {
        settings = buildSettings();
        storeFactory = std::make_unique<FileStoreFactory>(settings);
        logFactory = std::make_unique<FileLogFactory>(settings);
        initiator = std::make_unique<SSLSocketInitiator>(application, *storeFactory, settings, *logFactory);
    }

    void Client::connect()
    {
        initiator->start();
    }

    void Client::disconnect()
    {
        initiator->stop();
    }
    void Client::waitUntilConnected()
    {
        application.waitForLogon();
    }

    void Client::sendMessage(IMessage &message)
    {
        auto order = message.build();
        Session::sendToTarget(order, application.getSessionId());
    }

    void Client::onMessage(const Message &message, const SessionID &sessionID)
    {
        LOG_INFO("GOT A MESSAGE MOFOK");
    }

    SessionSettings Client::buildSettings()
    {
        std::map<std::string, std::map<std::string, std::string>> config = {
            {"DEFAULT", 
                {
                    {"BeginString", "FIX.4.4"}, 
                    {"SSLProtocol", "+SSLv3 +TLSv1 -SSLv2"}, 
                    {"ConnectionType", "initiator"}, 
                    {"ReconnectInterval", "60"}, 
                    {"TargetCompID", "SPOT"}, 
                    {"FileStorePath", "store"}, 
                    {"FileLogPath", "log"}, 
                    {"StartTime", "00:00:00"}, 
                    {"EndTime", "23:59:59"}, 
                    {"StartDay", "Sunday"}, 
                    {"EndDay", "Saturday"}, 
                    {"LogonDay", "Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday"}, 
                    {"LogoutDay", "Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday"}, 
                    {"LogonTime", "00:00:00"}, {"LogoutTime", "23:59:59"}, {"HeartBtInt", "30"}, 
                    {"UseDataDictionary", "Y"}, {"ResetOnDisconnect", "Y"}, {"ResetOnLogon", "Y"}, 
                    {"ResetOnLogout", "Y"}}},
            {"SESSION", 
                {
                    {"SocketConnectHost", this->getEndpoint()}, 
                    {"SocketConnectPort", this->getPort()}, 
                    {"SenderCompID", this->getSenderCompID()}, 
                    {"DataDictionary", this->getDictionnaryPath()}
                }
            }
        };

        std::stringstream cfg;

        for (const auto &section : config)
        {
            cfg << "[" << section.first << "]\n";
            for (const auto &kv : section.second)
            {
                cfg << kv.first << "=" << kv.second << "\n";
            }
            cfg << "\n";
        }

        return SessionSettings(cfg);
    }
}
