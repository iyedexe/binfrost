#include "BNBBroker_session.hpp"

bool BNBBroker_router_client::operator()(const FIX8::BNB::Heartbeat *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::Heartbeat *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}

bool BNBBroker_router_client::operator() (const FIX8::BNB::Logon *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::Logon *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}

bool BNBBroker_router_client::operator() (const FIX8::BNB::Logout *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::Logout *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}


bool BNBBroker_router_client::operator() (const FIX8::BNB::TestRequest *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::TestRequest *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}

bool BNBBroker_router_client::operator() (const FIX8::BNB::Reject *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::Reject *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}


bool BNBBroker_router_client::operator() (const FIX8::BNB::ExecutionReport *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::ExecutionReport *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}

bool BNBBroker_router_client::operator() (const FIX8::BNB::OrderCancelReject *msg) const
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_router_client::operator() (const FIX8::BNB::OrderCancelReject *msg) = ["<< message_str << "]"<< std::endl;
   return true;
}

/*
bool BNBBroker_router_client::operator() (const FIX8::BNB::News *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::NewOrderSingle *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::NewOrderList *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::OrderCancelRequest *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::ListStatus *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::OrderCancelRequestAndNewOrderSingle *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::LimitQuery *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::LimitResponse *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::OrderMassCancelRequest *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::OrderMassCancelReport *msg) const
{

}
*/

bool BNBBroker_session_client::handle_logon(const unsigned seqnum, const FIX8::Message *msg)
{
   std::string message_str;
   msg->encode(message_str);
   std::cout << "BNBBroker_session_client::handle_logon, seqnum={" << seqnum <<"}, content={"<< message_str << "}" << std::endl;
   return true;
}

FIX8::Message *BNBBroker_session_client::generate_logon(const unsigned heartbeat_interval, const FIX8::f8String davi)
{
   if (sodium_init() < 0) {
      throw std::runtime_error("libsodium initialization failed.");
   }

   auto private_key = loadPrivateKey(std::getenv("PRIVATE_KEY_PATH"));
   auto public_key = loadPublicKey(std::getenv("PUBLIC_KEY_PATH"));

   std::string raw_data = logonRawData(private_key,
                                       public_key,
                                       "BROKER",
                                       "SPOT",
                                       std::to_string(1),
                                       // "20240612-08:52:21.613");
                                       getCurrentTimestamp());
   std::cout << "Signature :: " << raw_data << std::endl;


   FIX8::BNB::Logon *nos(new FIX8::BNB::Logon);

   *nos << new FIX8::BNB::EncryptMethod(0)
        << new FIX8::BNB::HeartBtInt(10) // heartbeat interval [5, 60]
        << new FIX8::BNB::RawDataLength(raw_data.size())
        << new FIX8::BNB::RawData(raw_data)
        << new FIX8::BNB::ResetSeqNumFlag("Y")
        << new FIX8::BNB::Username(std::getenv("API_KEY"))
        << new FIX8::BNB::MessageHandling(2)
        << new FIX8::BNB::ResponseMode(1);

   std::string encoded;
   nos->encode(encoded);
   std::cout << "Encoded payload :: " << encoded << std::endl;
   return nos;
}

bool BNBBroker_session_client::handle_logout(const unsigned seqnum, const FIX8::Message *msg)
{
   std::cout << "BNBBroker_session_client::handle_logout" << std::endl;
   return true;
}

// }
// Message *BNBBroker_session_client::generate_logout()
// {

// }
bool BNBBroker_session_client::handle_heartbeat(const unsigned seqnum, const FIX8::Message *msg)
{
   std::cout << "BNBBroker_session_client::handle_heartbeat" << std::endl;
   return true;
}
// Message *BNBBroker_session_client::generate_heartbeat(const f8String& testReqID)
// {

// }
// bool BNBBroker_session_client::handle_resend_request(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// Message *BNBBroker_session_client::generate_resend_request(const unsigned begin, const unsigned end=0)
// {

// }
// bool BNBBroker_session_client::handle_sequence_reset(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// Message *BNBBroker_session_client::generate_sequence_reset(const unsigned newseqnum, const bool gapfillflag=false)
// {

// }
// bool BNBBroker_session_client::handle_test_request(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// Message *BNBBroker_session_client::generate_test_request(const f8String& testReqID)
// {

// }
// bool BNBBroker_session_client::handle_reject(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// Message *BNBBroker_session_client::generate_reject(const unsigned seqnum, const char *what)
// {

// }
// bool BNBBroker_session_client::handle_admin(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// void BNBBroker_session_client::modify_outbound(FIX8::Message *msg)
// {

// }
// bool BNBBroker_session_client::authenticate(SessionID& id, const FIX8::Message *msg)
// {

// }

bool BNBBroker_session_client::handle_application(const unsigned seqnum, const FIX8::Message *&msg)
{
   std::cout << "BNBBroker_session_client::handle_application" << std::endl;
   return enforce(seqnum, msg) || msg->process(_router);
}

bool BNBBroker_session_client::handle_admin(const unsigned seqnum, const FIX8::Message *msg)
{
   std::cout << "BNBBroker_session_client::handle_admin" << std::endl;
   return enforce(seqnum, msg) || msg->process(_router);
}
