#include "ws/ApiClient.hpp"
#include "ws/requests/streams/Streams.hpp"
#include "logger.hpp"

int main()
{
    BNB::WS::ApiClient streamsClient("wss://testnet.binance.vision/ws");
    streamsClient.start();
    std::map<std::string, std::string> subscriptionStreams = {{"btcusdt","trade"}};
    streamsClient.sendRequest(BNB::WS::Streams::Subscribe(subscriptionStreams));
    while (true)
    {
        auto message = streamsClient.getLastUpdate();
        LOG_INFO("Update : {}", message.dump());
    }
    return 0;
}