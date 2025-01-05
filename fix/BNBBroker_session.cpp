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
std::string BNBBroker_session_client::getState()
{
   return get_session_state_string(get_session_state());
}


FIX8::Message *BNBBroker_session_client::generate_logon(const unsigned heartbeat_interval, const FIX8::f8String davi)
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

   auto logonRequest = RequestBuilder::buildLogonRequest(raw_data, heartbeat_interval, apiKey);

   return logonRequest;
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
bool BNBBroker_session_client::handle_sequence_reset(const unsigned seqnum, const FIX8::Message *msg)
{
   std::cout << "BNBBroker_session_client::handle_sequence_reset" << std::endl;
   return true;

}
// Message *BNBBroker_session_client::generate_sequence_reset(const unsigned newseqnum, const bool gapfillflag=false)
// {

// }
// bool BNBBroker_session_client::handle_test_request(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// Message *BNBBroker_session_client::generate_test_request(const f8String& testReqID)
// {

// }
bool BNBBroker_session_client::handle_reject(const unsigned seqnum, const FIX8::Message *msg)
{
   std::cout << "BNBBroker_session_client::handle_reject" << std::endl;
   return true;
}
// Message *BNBBroker_session_client::generate_reject(const unsigned seqnum, const char *what)
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
