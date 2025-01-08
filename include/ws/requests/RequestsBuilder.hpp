#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "logger.hpp"

class RequestsBuilder
{
public:

    static std::string basicRequest(const std::string& requestId, const std::string& method);
    static std::string paramsUnsignedRequest(const std::string& requestId, const std::string& method, const nlohmann::json& params);
    static std::string paramsSignedRequest(const std::string& requestId, const std::string& method, const std::map<std::string, std::string>& params);

private:
    inline static RequestsBuilder* instance = nullptr;
    RequestsBuilder(const std::string& apiKey, const std::string& secretKey)
     : apiKey_(apiKey), secretKey_(secretKey) {}

    std::string apiKey_;
    std::string secretKey_;
    bool loggedIn_{false};

public:
    RequestsBuilder(const RequestsBuilder&) = delete;
    RequestsBuilder& operator=(const RequestsBuilder&) = delete;

    // Static method to get the singleton instance
    static RequestsBuilder* getInstance(const std::string& apiKey, const std::string& secretKey) {
        instance = new RequestsBuilder(apiKey, secretKey);
        return instance;
    }
};
