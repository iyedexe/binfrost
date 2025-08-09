#include "fix/Client.hpp"
#include "codegen/fix/MD/fix44/Heartbeat.hpp"
#include "codegen/fix/MD/fix44/TestRequest.hpp"
#include "codegen/fix/MD/fix44/Reject.hpp"
#include "codegen/fix/MD/fix44/Logout.hpp"
#include "codegen/fix/MD/fix44/Logon.hpp"
#include "codegen/fix/MD/fix44/LimitQuery.hpp"
#include "codegen/fix/MD/fix44/LimitResponse.hpp"
#include "codegen/fix/MD/fix44/InstrumentListRequest.hpp"
#include "codegen/fix/MD/fix44/InstrumentList.hpp"
#include "codegen/fix/MD/fix44/MarketDataRequest.hpp"
#include "codegen/fix/MD/fix44/MarketDataRequestReject.hpp"
#include "codegen/fix/MD/fix44/MarketDataSnapshot.hpp"
#include "codegen/fix/MD/fix44/MarketDataIncrementalRefresh.hpp"
#include "codegen/fix/MD/fix44/News.hpp"

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
        void onMessage(const Message &message, const SessionID &sessionID){crack(message, sessionID);}    
        void onMessage(const FIX44::MD::Heartbeat& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::TestRequest& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::Reject& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::Logout& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::Logon& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::LimitQuery& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::LimitResponse& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::InstrumentListRequest& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::InstrumentList& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::MarketDataRequest& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::MarketDataRequestReject& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::MarketDataSnapshot& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::MarketDataIncrementalRefresh& message, const SessionID& sessionID) override;
        void onMessage(const FIX44::MD::News& message, const SessionID& sessionID) override;
        
    private:
        virtual std::string getEndpoint() { return "fix-md.testnet.binance.vision"; }
        virtual std::string getPort() { return "9000"; }
        virtual std::string getSenderCompID() { return "FEEDER"; }
        virtual std::string getDictionnaryPath() { return "../include/codegen/fix/MD/FIX44.xml"; }
    };
}
