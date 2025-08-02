#include "fix/MessageBuilder.hpp"

MessageBuilder::MessageBuilder(const std::string &apiKey, crypto::ed25519 &key) : apiKey_(apiKey),
                                                                                  key_(key)
{
}

void MessageBuilder::fillLogon(FIX::Message &message)
{

    std::ostringstream oss;
    oss << "A" << '\x01' << message.getHeader().getField(FIX::FIELD::SenderCompID) << '\x01' << message.getHeader().getField(FIX::FIELD::TargetCompID) << '\x01' << message.getHeader().getField(FIX::FIELD::MsgSeqNum) << '\x01' << message.getHeader().getField(FIX::FIELD::SendingTime);
    std::string payload = oss.str();
    auto signatue = key_.sign(payload);

    message.setField(96, signatue);                        // RawData
    message.setField(95, std::to_string(signatue.size())); // RawDataLength
    message.setField(141, "Y");                            // ResetSeqNumFlag
    message.setField(553, apiKey_);                        // Username
    message.setField(25035, "2");                          // MessageHandling
}