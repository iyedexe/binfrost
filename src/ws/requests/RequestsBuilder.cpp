#include "ws/requests/RequestsBuilder.hpp"

std::string RequestsBuilder::basicRequest(const std::string& requestId, const std::string& method)
{
    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method}
    };

    return requestBody.dump();
}

std::string RequestsBuilder::paramsUnsignedRequest(const std::string& requestId, const std::string& method, const nlohmann::json& params)
{
    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method},
        {"params", params}
    };
    return requestBody.dump();
}

std::string RequestsBuilder::paramsSignedRequest(const std::string& requestId, const std::string& method, const std::map<std::string, std::string>& params)
{
    if (instance == nullptr) {
        LOG_ERROR("[REQUESTS_BUILDER] Singleton is not yet initialized.");
        return "";
    }

    std::string payload = RequestsHelper::generatePayload(params);
    std::string signature = signatureKey_->sign(payload);

    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method},
        {"params", params},
        {"signature", signature}
    };
    // std::string requestId = RequestsHelper::generateRequestId();
    // nlohmann::json requestBody = {
    //     {"id", requestId},
    //     {"method", method},
    //     {"params", params}
    // };

    // return std::make_pair(requestId, requestBody.dump());
}