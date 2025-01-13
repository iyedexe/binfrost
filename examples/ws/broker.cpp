#include "ws/ApiClient.hpp"
#include "crypto/ikey.hpp"
#include "ws/requests/RequestsBuilder.hpp"
#include "ws/requests/api/General.hpp"
#include "ws/requests/api/Trading.hpp"
#include "ws/requests/Parameters.hpp"
#include "logger.hpp"

int main()
{
    BNB::WS::ApiClient apiClient("wss://testnet.binance.vision/ws-api/v3");
    std::string apiKey = std::getenv("API_KEY");
    std::string secretKey = std::getenv("SECRET_KEY");
    crypto::KeyType keyType = crypto::KeyType::HMAC;

    RequestsBuilder::getInstance(apiKey, secretKey, keyType);

    apiClient.start();

    
    auto reqId = apiClient.sendRequest(
        BNB::WS::General::ExchangeInfo() << BNB::WS::Permissions({"SPOT"})
    );

    auto response = apiClient.getResponseForId(reqId);
    LOG_INFO("Response : {}", response.dump());

    LOG_INFO("Sleeping for 2 secs..");  
    std::this_thread::sleep_for(std::chrono::seconds(2));
    LOG_INFO("Testing order..");  

    reqId = apiClient.sendRequest(
        BNB::WS::Trading::TestNewOrder() 
            << BNB::WS::Symbol("XRPUSDC") 
            << BNB::WS::Side("BUY") 
            << BNB::WS::Type("MARKET")
            << BNB::WS::Quantity(1)
    );

    response = apiClient.getResponseForId(reqId);
    LOG_INFO("Response : {}", response.dump());

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}