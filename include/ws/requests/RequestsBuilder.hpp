#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "logger.hpp"
#include "crypto/ed25519.hpp"
#include "crypto/hmac.hpp"

class RequestsBuilder
{
public:

    static std::string basicRequest(const std::string& requestId, const std::string& method);
    static std::string paramsSignedRequest(const std::string& requestId, const std::string& method, const nlohmann::json& jsonParams);
    static std::string streamsRequest(const std::string& requestId, const std::string& method, const std::map<std::string, std::string>& params);


    template <typename T>
    static std::string paramsUnsignedRequest(const std::string& requestId, const std::string& method, const T& params)
    {
        nlohmann::json requestBody = {
            {"id", requestId},
            {"method", method},
            {"params", params}
        };
        return requestBody.dump();
    }


private:
    inline static RequestsBuilder* instance = nullptr;
    RequestsBuilder(const std::string& apiKey, const std::string& secretKey, crypto::KeyType keyType)
     : apiKey_(apiKey), secretKey_(secretKey) 
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
    bool loggedIn_{false};

    static std::string generatePayload(const std::map<std::string, std::string>& params);
    static std::string getTimestamp();

public:
    RequestsBuilder(const RequestsBuilder&) = delete;
    RequestsBuilder& operator=(const RequestsBuilder&) = delete;

    // Static method to get the singleton instance
    static RequestsBuilder* getInstance(const std::string& apiKey, const std::string& secretKey, crypto::KeyType keyType) {
        instance = new RequestsBuilder(apiKey, secretKey, keyType);
        return instance;
    }
};
