#include "fix/BrokerSessionClient.hpp"

namespace BNB::FIX {

class Client : public FIX8::ClientSession<BNB::FIX::BrokerSessionClient> {
public:
    Client(const std::string& sessionConfigPath , const std::string& sessionName = "BROKER")
        : FIX8::ClientSession<BNB::FIX::BrokerSessionClient>(
            FIX8::BNB::ctx(), sessionConfigPath, sessionName) 
    {
        std::string hostName;
        if (from_or_default(_ses, "ip", hostName))
            _sock->setPeerHostName(hostName);
    }

    void start() {
        bool wait = true;
        unsigned send_seqnum = 0;
        this->start(wait, send_seqnum);
    }
};

}