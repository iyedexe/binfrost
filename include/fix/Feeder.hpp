#include <quickfix/Session.h>
#include "fix/Client.hpp"
#include "codegen/fix/MD/fix44/MarketDataSnapshot.hpp"
#include "codegen/fix/MD/fix44/MessageCracker.hpp"

using namespace FIX;

namespace BNB::FIX
{
    class Feeder : public Client, public FIX44::MD::MessageCracker
    {
    public:
        Feeder(const std::string &apiKey, crypto::ed25519 &key)
            : Client(apiKey, key) 
            {
                init();
            }
        void onMessage(const Message &message, const SessionID &sessionID);
        void onMessage(const FIX44::MD::MarketDataSnapshot& message, const SessionID& sessionID);

    private:
        virtual std::string getEndpoint() { return "fix-md.testnet.binance.vision"; }
        virtual std::string getPort() { return "9000"; }
        virtual std::string getSenderCompID() { return "FEEDER"; }
        virtual std::string getDictionnaryPath() { return "../codegen/fix/MD/FIX44.xml"; }
    };
}
