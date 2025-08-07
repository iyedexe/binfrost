
#include <iostream>
#include <sstream>

#include "crypto/ed25519.hpp"
#include "crypto/utils.hpp"
#include "fix/MessageBuilder.hpp"
#include "fix/messages/NewSingleOrder.hpp"
#include "fix/Broker.hpp"
#include "utils.hpp"
#include "logger.hpp"

int main()
{
    LOG_INFO("Starting Binance FIX Client ...");
    std::string apiKey = getEnvVar("API_KEY");
    std::string privateKeyPath = getEnvVar("PRIVATE_KEY_PATH");

    if (apiKey.empty() || privateKeyPath.empty())
    {
        LOG_ERROR("Missing BNB Credentials, please set the variables API_KEY and SECRET_KEY");
        return 1;
    }
    crypto::ed25519 key{readPemFile(privateKeyPath)};

    try
    {
        auto client = BNB::FIX::Broker(apiKey, key);
        client.connect();
        client.waitUntilConnected();
        LOG_WARNING("Press <ENTER> to continue");
        std::cin.get();
        auto order = NewSingleOrder("111", '1', '1', "BTCUSDT");
        order.orderQty(0.2);
        client.sendMessage(order);
        std::cin.get();

        client.disconnect();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
