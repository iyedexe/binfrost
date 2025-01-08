#include "crypto/hmac.hpp"

namespace crypto
{
    hmac::hmac(const std::string& secretKey) : secretKey_(secretKey) {}

    std::string hmac::sign(const std::string& payload)
    {
        unsigned char* digest;
        digest = HMAC(EVP_sha256(), secretKey_.c_str(), secretKey_.length(), (unsigned char*)payload.c_str(), payload.length(), NULL, NULL);
        char mdString[SHA256_DIGEST_LENGTH * 2 + 1];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
        }
        return std::string(mdString);
    }

}


