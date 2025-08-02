#pragma once

#include <quickfix/Message.h>
#include <string>
#include <vector>
#include "utils.hpp"
#include "crypto/ed25519.hpp"

class MessageBuilder
{
public:
    MessageBuilder(const std::string &apiKey, crypto::ed25519 &key);
    void fillLogon(FIX::Message &message);

private:
    std::string apiKey_;
    crypto::ed25519 key_;
};