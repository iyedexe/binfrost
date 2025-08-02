#include "fix/FixClient.hpp"

#include <iostream>
#include <sstream>
#include "crypto/ed25519.hpp"
#include "logger.hpp"
#include "utils.hpp"
#include "fix/MessageBuilder.hpp"

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
        auto client = FixClient(apiKey, key);
        client.connect();
        std::cout
            << "Press <ENTER> to quit" << std::endl;
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
