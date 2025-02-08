// #include "BrokerRouterClient.hpp"
#include "fix/Client.hpp"


int main() 
{
    auto client = BNB::FIX::Client("../config/session.xml","BROKER");

    std::cout << "Broker client session created" << std::endl;

    client.start();
    std::cout << "Broker client session started" << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}