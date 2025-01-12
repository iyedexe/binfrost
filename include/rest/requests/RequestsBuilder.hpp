#pragma once
#include <numeric>
#include "rest/requests/IRequest.hpp"
#include "crypto/ikey.hpp"
#include "crypto/ed25519.hpp"
#include "crypto/hmac.hpp"

namespace BNB::REST
{
    class RequestsBuilder
    {
    public:
        static http::request<http::dynamic_body> buildBasicRequest(http::verb method, const std::string& uri, const std::map<std::string, std::string>& params);
        static http::request<http::dynamic_body> buildApiKeyRequest(http::verb method, const std::string& target, const std::map<std::string, std::string>& params);
    private:
        inline static RequestsBuilder* instance = nullptr;
        RequestsBuilder(const std::string& apiKey, const std::string& secretKey, crypto::KeyType keyType, const std::string& endpoint)
        : apiKey_(apiKey), secretKey_(secretKey), endpoint_(endpoint) 
        {
            if (keyType == crypto::KeyType::ED25519) {
                signatureKey_ = new crypto::ed25519(secretKey_);
            } else if (keyType == crypto::KeyType::HMAC) {
                signatureKey_ = new crypto::hmac(secretKey_);
            }  
        }
        
        crypto::ikey* signatureKey_;
        std::string apiKey_;
        std::string secretKey_;
        std::string endpoint_;
        bool loggedIn_{false};

        static std::string generatePayload(const std::map<std::string, std::string>& params);
        static std::string getTimestamp();

    public:
        RequestsBuilder(const RequestsBuilder&) = delete;
        RequestsBuilder& operator=(const RequestsBuilder&) = delete;

        // Static method to get the singleton instance
        static RequestsBuilder* getInstance(const std::string& apiKey, const std::string& secretKey, crypto::KeyType keyType, const std::string& endpoint) {
            instance = new RequestsBuilder(apiKey, secretKey, keyType, endpoint);
            return instance;
        }

    };
}
