#include "rest/ApiClient.hpp"
#include "crypto/ikey.hpp"
#include "rest/requests/RequestsBuilder.hpp"
#include "rest/requests/UserStream.hpp"
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


    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}