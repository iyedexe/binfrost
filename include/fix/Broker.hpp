#include "fix/Client.hpp"

namespace BNB::FIX
{
    class Broker : public Client
    {
    public:
        Broker(const std::string &apiKey, crypto::ed25519 &key)
            : Client(apiKey, key) 
            {
                init();
            }

    private:
        virtual std::string getEndpoint() { return "fix-oe.testnet.binance.vision"; }
        virtual std::string getPort() { return "9000"; }
        virtual std::string getSenderCompID() { return "BROKER"; }
        virtual std::string getDictionnaryPath() { return "../codegen/fix/broker/FIX44.xml"; }
    };
}
