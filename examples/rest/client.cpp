#include "rest/ApiClient.hpp"
#include "crypto/ikey.hpp"
#include "rest/requests/RequestsBuilder.hpp"
#include "rest/requests/UserStream.hpp"
#include "logger.hpp"

int main()
{
    BNB::REST::ApiClient apiClient("testnet.binance.vision");
    std::string apiKey = std::getenv("API_KEY");
    std::string secretKey = std::getenv("SECRET_KEY");
    crypto::KeyType keyType = crypto::KeyType::HMAC;

    BNB::REST::RequestsBuilder::getInstance(apiKey, secretKey, keyType);

    auto response = apiClient.sendRequest(BNB::REST::UserStream::Start());
    LOG_INFO("Response: {}", response);


    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}