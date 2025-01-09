#pragma once
#include <string>

namespace crypto {
    class ikey {
    public:
        ikey() =default;
        virtual ~ikey() =default;

        virtual std::string sign(const std::string& payload) = 0;
    };
  
    enum class KeyType : uint8_t {  
        HMAC,
        ED25519,
        RSA,
    };
}