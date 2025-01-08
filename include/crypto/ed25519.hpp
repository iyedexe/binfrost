#include<vector>
#include <string>
#include <stdexcept>
#include <sodium.h>
#include "crypto/ikey.hpp"

namespace crypto {
    class ed25519 : public ikey {
    public:
        ed25519(const std::string& privateKey);
        ~ed25519();

        std::string sign(const std::string& message);
    private:
        std::vector<unsigned char> privateKey_;
        std::vector<unsigned char> publicKey_;
        std::vector<unsigned char> signatureKey_;

        std::vector<unsigned char> loadPrivateKeyFromString(const std::string& pem_key);
        std::vector<unsigned char> derivePublicKeyFromPrivate(const std::vector<unsigned char>& seed);

    };
}