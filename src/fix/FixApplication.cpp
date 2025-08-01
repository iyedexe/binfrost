#include "fix/FixApplication.hpp"
#include "utils.hpp"
#include "logger.hpp"

void FixApplication::onCreate(const FIX::SessionID &sessionID)
{
    LOG_INFO("Session created: {}", sessionID.toString());
}

void FixApplication::onLogon(const FIX::SessionID &sessionID)
{
    LOG_INFO("Logon: {}", sessionID.toString());
}

void FixApplication::onLogout(const FIX::SessionID &sessionID)
{
    LOG_INFO("Logout: {}", sessionID.toString());
}

void FixApplication::toAdmin(FIX::Message &message, const FIX::SessionID &sessionID)
{
    auto const &msgType = message.getHeader().getField(FIX::FIELD::MsgType);

    if (msgType == "A")
    {
        LOG_INFO("Building logon message");
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
        LOG_INFO("Sending Admin: {}", message.toString());
    }
}

void FixApplication::fromAdmin(const FIX::Message &message, const FIX::SessionID &sessionID)
    QUICKFIX_THROW(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon)
{
    LOG_INFO("Received Admin: {}", message.toString());
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
}
