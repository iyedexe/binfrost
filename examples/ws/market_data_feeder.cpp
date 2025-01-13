#include "ws/ApiClient.hpp"
#include "ws/requests/streams/Streams.hpp"
#include "ws/requests/Parameters.hpp"
#include "logger.hpp"

int main()
{
    BNB::WS::ApiClient streamsClient("wss://testnet.binance.vision/ws");
    streamsClient.start();

    streamsClient.sendRequest(
        BNB::WS::Streams::Subscribe() 
            << BNB::WS::TradeStream("btcusdt")
    );
    while (true)
    {
        auto message = streamsClient.getLastUpdate();
        LOG_INFO("Update : {}", message.dump());
    }
    return 0;
}