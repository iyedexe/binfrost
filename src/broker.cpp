// #include "BrokerRouterClient.hpp"
#include "BrokerSessionClient.hpp"


int main()
{
    FIX8::ClientSession<FIX::BNB::BrokerSessionClient>::ClientSession_ptr mc(
        new FIX8::ClientSession<FIX::BNB::BrokerSessionClient>(
            FIX8::BNB::ctx(),
            "../config/session.xml",
            "BROKER"
        )
    );
    std::cout << "Broker client session created" << std::endl;

    bool wait = true;
    unsigned send_seqnum=0;
    mc->start(wait, send_seqnum);
    std::cout << "Broker client session started" << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}