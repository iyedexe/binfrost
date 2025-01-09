#pragma once
#include <string>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include "crypto/ikey.hpp"

namespace crypto {
    class hmac : public ikey {
    public:
        hmac(const std::string& secretKey);
        ~hmac() = default;

        std::string sign(const std::string& payload);
    
    private:
        std::string secretKey_;
    };
}