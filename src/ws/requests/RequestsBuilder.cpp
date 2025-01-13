#include "ws/requests/RequestsBuilder.hpp"

std::string RequestsBuilder::basicRequest(const std::string& requestId, const std::string& method)
{
    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method}
    };

    return requestBody.dump();
}

std::string RequestsBuilder::streamsRequest(const std::string& requestId, const std::string& method, const nlohmann::json& jsonParams)
{
    std::vector<std::string> params; 
    for (const auto& [key, value] : jsonParams.items()) {
        if (value.is_string()) {
            params.push_back(value.get<std::string>() + "@" + key);
        } else {
            params.push_back(value.dump() + "@" + key);
        }   
    }
    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method},
        {"params", params}
    };
    return requestBody.dump();
}


std::string RequestsBuilder::paramsSignedRequest(const std::string& requestId, const std::string& method, const nlohmann::json& jsonParams)
{
    if (instance == nullptr) {
        LOG_ERROR("[REQUESTS_BUILDER] Singleton is not yet initialized.");
        return "";
    }

    std::map<std::string, std::string> signedParams;
    for (const auto& [key, value] : jsonParams.items()) {
        // LOG_DEBUG("Dumping parameter {}, {}", key, value.dump());
        if (value.is_string()) {
            signedParams[key] = value.get<std::string>();
        } else {
            signedParams[key] = value.dump();
        }
    }

    signedParams.insert({"apiKey", instance->apiKey_});
    signedParams.insert({"timestamp", getTimestamp()});

    std::string payload = generatePayload(signedParams);
    std::string signature = instance->signatureKey_->sign(payload);
    signedParams.insert({"signature", signature});

    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method},
        {"params", signedParams},
    };
    return requestBody.dump();
}

std::string RequestsBuilder::generatePayload(const std::map<std::string, std::string>& params) {
    return std::accumulate(
        params.begin(),
        params.end(),
        std::string(),
        [](const std::string& acc, const std::pair<std::string, std::string>& param) {
            return acc.empty()
                ? param.first + "=" + param.second
                : acc + "&" + param.first + "=" + param.second;
        });
}

std::string RequestsBuilder::getTimestamp(){
    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::to_string(milliseconds);
}
