#include "BNBBroker_session.hpp"


int main()
{
    FIX8::ClientSession<BNBBroker_session_client>::ClientSession_ptr mc(
        new FIX8::ClientSession<BNBBroker_session_client>(
            FIX8::BNB::ctx(),
            "../config/session1.xml",
            "BROKER"
        )
    );
    std::cout << "Broker client session created" << std::endl;

    mc->start(true);
    std::cout << "Broker client session started" << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}