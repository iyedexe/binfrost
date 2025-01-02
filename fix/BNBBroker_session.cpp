#include "BNBBroker_session.hpp"


// Override these methods to receive specific message callbacks.
bool BNBBroker_router_client::operator()(const FIX8::BNB::Heartbeat *msg) const
{
   return false;
}
/*
bool BNBBroker_router_client::operator() (const FIX8::BNB::TestRequest *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::Reject *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::Logout *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::ExecutionReport *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::OrderCancelReject *msg) const
{

}

bool BNBBroker_router_client::operator() (const FIX8::BNB::Logon *msg) const
{

}

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
   std::cout << "BNBBroker_session_client::handle_logon" << std::endl;
   return false;
}

FIX8::Message *BNBBroker_session_client::generate_logon(const unsigned heartbeat_interval, const FIX8::f8String davi)
{
   return nullptr;
}

// bool BNBBroker_session_client::handle_logout(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
// Message *BNBBroker_session_client::generate_logout()
// {

// }
// bool BNBBroker_session_client::handle_heartbeat(const unsigned seqnum, const FIX8::Message *msg)
// {

// }
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
   return enforce(seqnum, msg) || msg->process(_router);
}
