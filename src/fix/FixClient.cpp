#include <sstream>
#include <iostream>
#include "fix/FixClient.hpp"
#include "utils.hpp"
#include "logger.hpp"


FixClient::FixClient(const std::string &apiKey, crypto::ed25519 &key)
    : application(apiKey, key),
      settings(buildSettings()),
      storeFactory(settings),
      logFactory(settings),
      initiator(application, storeFactory, settings, logFactory)
{
    application.setClient(this);
}

void FixClient::connect()
{
    initiator.start();
}

void FixClient::disconnect()
{
    initiator.stop();
}
void FixClient::waitUntilConnected()
{
    application.waitForLogon();
}

void FixClient::sendMessage(IMessage &message)
{
    auto order = message.build();
    order.getHeader().setField(FIX::SenderCompID("CLIENT1"));
    order.getHeader().setField(FIX::TargetCompID("SPOT"));
    FIX::Session::sendToTarget(order);
}

void FixClient::onMessage()
{
    LOG_INFO("GOT A MESSAGE MOFOK");
}

FIX::SessionSettings FixClient::buildSettings()
{
    std::map<std::string, std::map<std::string, std::string>> config = {
        {
            "DEFAULT", {
                {"SSLProtocol", "+SSLv3 +TLSv1 -SSLv2"},
                {"ConnectionType", "initiator"},
                {"ReconnectInterval", "60"},
                {"SenderCompID", "CLIENT1"},
                {"TargetCompID", "SPOT"},
                {"FileStorePath", "store"},
                {"FileLogPath", "log"},
                {"StartTime", "00:00:00"},
                {"EndTime", "23:59:59"},
                {"StartDay", "Sunday"},
                {"EndDay", "Saturday"},
                {"LogonDay", "Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday"},
                {"LogoutDay", "Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday"},
                {"LogonTime", "00:00:00"},
                {"LogoutTime", "23:59:59"},
                {"HeartBtInt", "30"},
                {"UseDataDictionary", "N"},
                {"DataDictionary", "spec/FIX44.xml"},
                {"SocketConnectHost", "fix-oe.testnet.binance.vision"},
                {"SocketConnectPort", "9000"},
                {"ResetOnDisconnect", "Y"},
                {"ResetOnLogon", "Y"},
                {"ResetOnLogout", "Y"}
            }
        },
        {
            "SESSION", {
                {"BeginString", "FIX.4.4"}
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

    return FIX::SessionSettings(cfg);
}
