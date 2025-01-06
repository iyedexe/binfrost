#include "BrokerSessionClient.hpp"

namespace FIX
{
    namespace BNB
    {
        bool BrokerSessionClient::handle_logon(const unsigned seqnum, const FIX8::Message *msg)
        {
        std::stringstream messageStream;
        msg->print(messageStream);
        std::cout << "BrokerSessionClient::handle_logon, seqnum={" << seqnum <<"}, content={"<< messageStream.str() << "}" << std::endl;
        return true;
        }
        std::string BrokerSessionClient::getState()
        {
        return get_session_state_string(get_session_state());
        }


        FIX8::Message *BrokerSessionClient::generate_logon(const unsigned heartbeat_interval, const FIX8::f8String davi)
        {
        std::vector<unsigned char> privateKey = loadPrivateKeyFromString(readPemFile(std::getenv("PRIVATE_KEY_PATH")));
        std::vector<unsigned char> publicKey = derivePublicKeyFromPrivate(privateKey);
        std::string sendingTime = getCurrentTimestamp();
        const unsigned sequence_number = _next_send_seq;
        std::cout << "sequence_number: " << sequence_number << std::endl;
        std::string senderCompID = "BROKER";
        std::string targetCompID = "SPOT"; 
        std::string apiKey = std::getenv("API_KEY");
        
        std::string raw_data = logonRawData(
            privateKey,
            publicKey,
            senderCompID,
            targetCompID,
            std::to_string(sequence_number),
            sendingTime
        );
        std::cout << "Used sending time" << sendingTime << std::endl;
        lastSendingTime_ = sendingTime;
        auto logonRequest = RequestBuilder::buildLogonRequest(raw_data, heartbeat_interval, apiKey);
        return logonRequest;
        }

        bool BrokerSessionClient::handle_logout(const unsigned seqnum, const FIX8::Message *msg)
        {
        std::cout << "BrokerSessionClient::handle_logout" << std::endl;
        return true;
        }

        // }
        // Message *BrokerSessionClient::generate_logout()
        // {

        // }
        bool BrokerSessionClient::handle_heartbeat(const unsigned seqnum, const FIX8::Message *msg)
        {
        std::cout << "BrokerSessionClient::handle_heartbeat" << std::endl;
        return true;
        }
        // Message *BrokerSessionClient::generate_heartbeat(const f8String& testReqID)
        // {

        // }
        // bool BrokerSessionClient::handle_resend_request(const unsigned seqnum, const FIX8::Message *msg)
        // {

        // }
        // Message *BrokerSessionClient::generate_resend_request(const unsigned begin, const unsigned end=0)
        // {

        // }
        bool BrokerSessionClient::handle_sequence_reset(const unsigned seqnum, const FIX8::Message *msg)
        {
        std::cout << "BrokerSessionClient::handle_sequence_reset" << std::endl;
        return true;

        }
        // Message *BrokerSessionClient::generate_sequence_reset(const unsigned newseqnum, const bool gapfillflag=false)
        // {

        // }
        // bool BrokerSessionClient::handle_test_request(const unsigned seqnum, const FIX8::Message *msg)
        // {

        // }
        // Message *BrokerSessionClient::generate_test_request(const f8String& testReqID)
        // {

        // }
        bool BrokerSessionClient::handle_reject(const unsigned seqnum, const FIX8::Message *msg)
        {
        std::stringstream messageStream;
        msg->print(messageStream);
        std::cout << "BrokerSessionClient::handle_reject, seqnum={" << seqnum <<"}, content={"<< messageStream.str() << "}" << std::endl;
        return true;
        }
        // Message *BrokerSessionClient::generate_reject(const unsigned seqnum, const char *what)
        // {

        // }
        // void BrokerSessionClient::modify_outbound(FIX8::Message *msg)
        // {

        // }
        // bool BrokerSessionClient::authenticate(SessionID& id, const FIX8::Message *msg)
        // {

        // }

        bool BrokerSessionClient::handle_application(const unsigned seqnum, const FIX8::Message *&msg)
        {
        std::cout << "BrokerSessionClient::handle_application" << std::endl;
        return enforce(seqnum, msg) || msg->process(_router);
        }

        bool BrokerSessionClient::handle_admin(const unsigned seqnum, const FIX8::Message *msg)
        {
        std::stringstream messageStream;
        msg->print(messageStream);
        std::cout << "BrokerSessionClient::handle_admin, seqnum={" << seqnum <<"}, content={"<< messageStream.str() << "}" << std::endl;
        return enforce(seqnum, msg) || msg->process(_router);
        }


        int BrokerSessionClient::modify_header(FIX8::MessageBase *msg)
        {
        msg->add_field(new FIX8::BNB::SendingTime(lastSendingTime_));
        return 0;
        }
    }
}

