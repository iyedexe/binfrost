#pragma once

#include <fix8/f8config.h>
#include <fix8/f8includes.hpp>      // Core FIX8 includes
#include <fix8/f8types.hpp>         // Core FIX8 types
#include <fix8/usage.hpp>           // For session usage utilities
#include "fix/oe/broker_router.hpp"
#include "fix/oe/broker_types.hpp"
#include "fix/oe/broker_classes.hpp"
#include "BrokerRouterClient.hpp"
#include "utils.hpp"

class RequestBuilder {
public:
   static FIX8::BNB::Logon* buildLogonRequest(const std::string& rawData,const unsigned heartbeat_interval, const std::string& apiKey)
   {
      FIX8::BNB::Logon* nos = new FIX8::BNB::Logon();

      *nos << new FIX8::BNB::RawDataLength(rawData.size())
            << new FIX8::BNB::RawData(rawData)
            << new FIX8::BNB::EncryptMethod(0)
            << new FIX8::BNB::HeartBtInt(heartbeat_interval)
            << new FIX8::BNB::ResetSeqNumFlag("Y")
            << new FIX8::BNB::Username(apiKey)
            << new FIX8::BNB::MessageHandling(2);

      return nos;
   }
};

namespace BNB
{
    namespace FIX
    {
        class BrokerSessionClient : public FIX8::Session
        {
        BrokerRouterClient _router; 
        std::string lastSendingTime_;

        public:
        BrokerSessionClient(const FIX8::F8MetaCntx& ctx, const FIX8::SessionID& sid, FIX8::Persister *persist=0,
            FIX8::Logger *logger=0, FIX8::Logger *plogger=0) : Session(ctx, sid, persist, logger, plogger), _router(*this) {} 

        bool handle_logon(const unsigned seqnum, const FIX8::Message *msg);
        FIX8::Message *generate_logon(const unsigned heartbeat_interval, const FIX8::f8String davi=FIX8::f8String());
        bool handle_logout(const unsigned seqnum, const FIX8::Message *msg);
        // Message *generate_logout();
        bool handle_heartbeat(const unsigned seqnum, const FIX8::Message *msg);
        // Message *generate_heartbeat(const f8String& testReqID);
        // bool handle_resend_request(const unsigned seqnum, const FIX8::Message *msg);
        // Message *generate_resend_request(const unsigned begin, const unsigned end=0);
        bool handle_sequence_reset(const unsigned seqnum, const FIX8::Message *msg);
        // Message *generate_sequence_reset(const unsigned newseqnum, const bool gapfillflag=false);
        // bool handle_test_request(const unsigned seqnum, const FIX8::Message *msg);
        // Message *generate_test_request(const f8String& testReqID);
        bool handle_reject(const unsigned seqnum, const FIX8::Message *msg);
        // Message *generate_reject(const unsigned seqnum, const char *what);
        // bool handle_admin(const unsigned seqnum, const FIX8::Message *msg);
        // void modify_outbound(FIX8::Message *msg);
        // bool authenticate(SessionID& id, const FIX8::Message *msg);

        // Override these methods to intercept admin and application methods.
        bool handle_admin(const unsigned seqnum, const FIX8::Message *msg);
        bool handle_application(const unsigned seqnum, const FIX8::Message *&msg);   
        int modify_header(FIX8::MessageBase *msg);

        };
    }
}
