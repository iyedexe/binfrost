#include "crypto/ed25519.hpp"
#include "crypto/utils.hpp"

#include <iostream>
namespace crypto
{
    ed25519::ed25519(const std::string &pemPrivateKey)
    {
        if (sodium_init() < 0)
        {
            throw std::runtime_error("libsodium initialization failed.");
        }
        std::string barePemKey = stripPrivateKey(pemPrivateKey);
        privateKey_ = loadPrivateKeyFromString(barePemKey);
        publicKey_ = derivePublicKeyFromPrivate(privateKey_);

        signatureKey_.insert(signatureKey_.end(), privateKey_.begin(), privateKey_.end());
        signatureKey_.insert(signatureKey_.end(), publicKey_.begin(), publicKey_.end());
    }

    std::vector<unsigned char> ed25519::derivePublicKeyFromPrivate(const std::vector<unsigned char> &seed)
    {
        std::vector<unsigned char> pk(crypto_sign_PUBLICKEYBYTES);
        std::vector<unsigned char> sk(crypto_sign_SECRETKEYBYTES);

        if (crypto_sign_seed_keypair(pk.data(), sk.data(), seed.data()) != 0)
        {
            throw std::runtime_error("Failed to derive public key");
        }
        return pk;
    }

    std::vector<unsigned char> ed25519::loadPrivateKeyFromString(const std::string &barePemKey)
    {
        // Decode base64-encoded PEM content into binary
        std::vector<unsigned char> privateKey(crypto_sign_ed25519_SECRETKEYBYTES);
        if (sodium_base642bin(privateKey.data(), privateKey.size(),
                              barePemKey.c_str(), barePemKey.size(),
                              nullptr, nullptr, nullptr,
                              sodium_base64_VARIANT_ORIGINAL) != 0)
        {
            throw std::runtime_error("Failed to decode PEM key.");
        }
        std::vector<unsigned char> secretKey(privateKey.begin() + 16, privateKey.end() - 16);
        return secretKey;
    }

    std::string ed25519::sign(const std::string &message)
    {

        std::vector<unsigned char> payload;
        payload.insert(payload.end(), message.begin(), message.end());

        std::vector<unsigned char> signature(crypto_sign_ed25519_BYTES);
        if (crypto_sign_detached(signature.data(),
                                 nullptr,
                                 payload.data(),
                                 payload.size(),
                                 signatureKey_.data()) != 0)
        {
            throw std::runtime_error("Signing failed.");
        }

        std::vector<char> b64_signature(sodium_base64_encoded_len(signature.size(), sodium_base64_VARIANT_ORIGINAL));
        sodium_bin2base64(b64_signature.data(),
                          b64_signature.size(),
                          signature.data(),
                          signature.size(),
                          sodium_base64_VARIANT_ORIGINAL);

        return std::string(b64_signature.data());
    }
}
