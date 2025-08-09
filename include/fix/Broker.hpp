#include "fix/Client.hpp"
#include "codegen/fix/OE/fix44/Heartbeat.hpp"

#include "codegen/fix/OE/fix44/MessageCracker.hpp"

namespace BNB::FIX
{
    class Broker : public Client, public FIX44::OE::MessageCracker
    {
    public:
        Broker(const std::string &apiKey, crypto::ed25519 &key)
            : Client(apiKey, key) 
            {
                init();
            }
        void onMessage(const Message &message, const SessionID &sessionID){crack(message, sessionID);}    
        void onMessage(const FIX44::OE::Heartbeat& message, const SessionID& sessionID) override;

    private:
        virtual std::string getEndpoint() { return "fix-oe.testnet.binance.vision"; }
        virtual std::string getPort() { return "9000"; }
        virtual std::string getSenderCompID() { return "BROKER"; }
        virtual std::string getDictionnaryPath() { return "..include/codegen/fix/OE/FIX44.xml"; }
    };
}
