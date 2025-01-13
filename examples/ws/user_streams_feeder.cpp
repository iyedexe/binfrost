#include <nlohmann/json.hpp>

#include "crypto/ikey.hpp"

#include "rest/ApiClient.hpp"
#include "rest/requests/RequestsBuilder.hpp"
#include "rest/requests/UserStream.hpp"

#include "ws/ApiClient.hpp"
#include "ws/requests/streams/Streams.hpp"
#include "ws/requests/Parameters.hpp"

#include "logger.hpp"

int main()
{
    std::string apiKey = std::getenv("API_KEY");
    std::string secretKey = std::getenv("SECRET_KEY");
    crypto::KeyType keyType = crypto::KeyType::HMAC;
    std::string endpoint = "testnet.binance.vision";

    BNB::REST::ApiClient apiClient(endpoint);
    BNB::REST::RequestsBuilder::getInstance(apiKey, secretKey, keyType, endpoint);

    auto response = apiClient.sendRequest(BNB::REST::UserStream::Start());
    LOG_INFO("Response: {}", response);

    auto jsonData = nlohmann::json::parse(response);
    std::string listenKey = jsonData["listenKey"];

    BNB::WS::ApiClient streamsClient("wss://testnet.binance.vision/ws");
    streamsClient.start();
    streamsClient.sendRequest(BNB::WS::Streams::Subscribe() << BNB::WS::UserStream(listenKey));
    while (true)
    {
        auto message = streamsClient.getLastUpdate();
        LOG_INFO("Update : {}", message.dump());
    }
    return 0;
}