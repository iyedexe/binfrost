#include "ws/ApiClient.hpp"
#include "crypto/ikey.hpp"
#include "ws/requests/RequestsBuilder.hpp"
#include "ws/requests/api/Account.hpp"

int main()
{
    BNB::WS::ApiClient apiClient("wss://testnet.binance.vision/ws-api/v3");
    std::string apiKey = std::getenv("API_KEY");
    std::string secretKey = std::getenv("SECRET_KEY");
    crypto::KeyType keyType = crypto::KeyType::HMAC;

    RequestsBuilder::getInstance(apiKey, secretKey, keyType);

    apiClient.start();

    auto reqId = apiClient.sendRequest(BNB::WS::Account::Information());
    std::cout << "Request ID: " << reqId << std::endl;


    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}