#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/SSLSocketInitiator.h"

#include <iostream>
#include <sstream>

#include "utils.hpp"

class InlineClient : public FIX::Application, public FIX::MessageCracker
{
public:
    void onCreate(const FIX::SessionID &sessionID) override
    {
        std::cout << "Session created: " << sessionID << "\n";
    }

    void onLogon(const FIX::SessionID &sessionID) override
    {
        std::cout << "Logon: " << sessionID << "\n";
    }

    void onLogout(const FIX::SessionID &sessionID) override
    {
        std::cout << "Logout: " << sessionID << "\n";
    }

    void toAdmin(FIX::Message &message, const FIX::SessionID &sessionID) override
    {
        auto const &msgType = message.getHeader().getField(FIX::FIELD::MsgType);

        if (msgType == "A")
        {
            std::cout << "Building logon message" << std::endl;
            std::vector<unsigned char> privateKey = loadPrivateKeyFromString(readPemFile(std::getenv("PRIVATE_KEY_PATH")));
            std::vector<unsigned char> publicKey = derivePublicKeyFromPrivate(privateKey);
            std::string apiKey = std::getenv("API_KEY");
            auto const &clSenderCompID = message.getHeader().getField(FIX::FIELD::SenderCompID);
            auto const &clTargetCompID = message.getHeader().getField(FIX::FIELD::TargetCompID);
            auto const &clSendingTime = message.getHeader().getField(FIX::FIELD::SendingTime);
            auto const &clMsgSeqNum = message.getHeader().getField(FIX::FIELD::MsgSeqNum);

            std::string raw_data = logonRawData(
                privateKey,
                publicKey,
                clSenderCompID,
                clTargetCompID,
                clMsgSeqNum,
                clSendingTime);

            message.setField(96, raw_data);                        // RawData
            message.setField(95, std::to_string(raw_data.size())); // RawDataLength
            message.setField(141, "Y");                            // ResetSeqNumFlag
            message.setField(553, apiKey);                         // Username
            message.setField(25035, "2");                          // MessageHandling
            std::cout << "Sending Admin: " << message.toString() << "\n";
        }
    }

    void fromAdmin(const FIX::Message &message, const FIX::SessionID &sessionID)
        QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) override
    {
        std::cout << "Received Admin: " << message.toString() << "\n";
    }

    void toApp(FIX::Message &message, const FIX::SessionID &sessionID)
        QUICKFIX_THROW(FIX::DoNotSend) override
    {
        std::cout << "Sending App: " << message.toString() << "\n";
    }
    void fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
        QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) override
    {
        crack(message, sessionID);
    }
};

int main()
{
    try
    {
        // Define config inline
        std::stringstream cfg;
        cfg << R"(
            [DEFAULT]
            SSLProtocol = +SSLv3 +TLSv1 -SSLv2
            ConnectionType=initiator
            ReconnectInterval=60
            SenderCompID=CLIENT1
            TargetCompID=SPOT
            FileStorePath=store
            FileLogPath=log
            StartTime=00:00:00
            EndTime=23:59:59
            StartDay=Sunday
            EndDay=Saturday
            LogonDay=Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday
            LogoutDay=Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday
            LogonTime=00:00:00
            LogoutTime=23:59:59
            HeartBtInt=30
            UseDataDictionary=N
            DataDictionary=spec/FIX44.xml
            SocketConnectHost=fix-oe.testnet.binance.vision
            SocketConnectPort=9000
            ResetOnDisconnect=Y

            [SESSION]
            BeginString=FIX.4.4
            )";

        FIX::SessionSettings settings(cfg);
        InlineClient application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::FileLogFactory logFactory(settings);
        FIX::SSLSocketInitiator initiator(application, storeFactory, settings, logFactory);

        initiator.start();
        std::cout << "Press <ENTER> to quit" << std::endl;
        std::cin.get();
        initiator.stop();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
