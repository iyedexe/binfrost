#include "rest/ApiClient.hpp"
#include "crypto/ikey.hpp"
#include "rest/requests/RequestsBuilder.hpp"
#include "rest/requests/UserStream.hpp"
#include "rest/requests/endpoints/MarketData.hpp"
#include "rest/requests/endpoints/General.hpp"
#include "rest/requests/endpoints/Account.hpp"
#include "logger.hpp"

#ifndef OPENSSL_CONF_PATH
#define OPENSSL_CONF_PATH ""
#endif

std::string getEnvVar(const char* varName) {
    const char* val = std::getenv(varName);
    return val ? std::string(val) : std::string();
}

int main()
{
    if ((!std::getenv("OPENSSL_CONF")) && OPENSSL_CONF_PATH[0] != '\0') {
        setenv("OPENSSL_CONF", OPENSSL_CONF_PATH, /*overwrite=*/0);
    }

    LOG_INFO("Starting Binance REST Client ...");
    std::string apiKey = getEnvVar("API_KEY");
    std::string secretKey = getEnvVar("SECRET_KEY");

    if (apiKey.empty() || secretKey.empty())
    {
        LOG_ERROR("Missing BNB Credentials, please set the variables API_KEY and SECRET_KEY");
        return 1;
    }
    crypto::KeyType keyType = crypto::KeyType::HMAC;
    std::string endpoint = "testnet.binance.vision";

    BNB::REST::ApiClient apiClient(endpoint);
    BNB::REST::RequestsBuilder::getInstance(apiKey, secretKey, keyType, endpoint);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    LOG_INFO("Send Request GeneralEndpoint::Time");
    auto response = apiClient.sendRequest(BNB::REST::Endpoints::General::Time());
    LOG_INFO("Response: {}", response);

    LOG_INFO("Send Request General::ExchangeInfo");
    response = apiClient.sendRequest(BNB::REST::Endpoints::General::ExchangeInfo().symbol("MASKUSDC"));
    LOG_INFO("Response: {}", response);


    LOG_INFO("Send Request MarketData::OrderBook");
    response = apiClient.sendRequest(BNB::REST::Endpoints::MarketData::OrderBook().symbol("MASKUSDC"));
    LOG_INFO("Response: {}", response);

    LOG_INFO("Send Request Account::AccountInformation");
    response = apiClient.sendRequest(BNB::REST::Endpoints::Account::AccountInformation());
    LOG_INFO("Response: {}", response);

/*
    LOG_INFO("Send Request UserStream::Start");
    auto response = apiClient.sendRequest(BNB::REST::UserStream::Start());
    LOG_INFO("Response: {}", response);
*/
    
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}