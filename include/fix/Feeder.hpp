#include "fix/Client.hpp"

namespace BNB::FIX
{
    class Feeder : public Client
    {
    public:
        Feeder(const std::string &apiKey, crypto::ed25519 &key)
            : Client(apiKey, key) 
            {
                init();
            }

    private:
        virtual std::string getEndpoint() { return "fix-md.testnet.binance.vision"; }
        virtual std::string getPort() { return "9000"; }
        virtual std::string getSenderCompID() { return "FEEDER"; }
        virtual std::string getDictionnaryPath() { return "../codegen/fix/feeder/FIX44.xml"; }
    };
}
