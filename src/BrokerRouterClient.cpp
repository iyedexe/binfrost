#include "BrokerRouterClient.hpp"

namespace FIX
{
    namespace BNB
    {
        bool BrokerRouterClient::operator()(const FIX8::BNB::Heartbeat *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::Heartbeat *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::Logon *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::Logon *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::Logout *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::Logout *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }


        bool BrokerRouterClient::operator() (const FIX8::BNB::TestRequest *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::TestRequest *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::Reject *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::Reject *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }


        bool BrokerRouterClient::operator() (const FIX8::BNB::ExecutionReport *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::ExecutionReport *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::OrderCancelReject *msg) const
        {
            std::string message_str;
            msg->encode(message_str);
            std::cout << "BrokerRouterClient::operator() (const FIX8::BNB::OrderCancelReject *msg) = ["<< message_str << "]"<< std::endl;
            return true;
        }

        /*
        bool BrokerRouterClient::operator() (const FIX8::BNB::News *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::NewOrderSingle *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::NewOrderList *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::OrderCancelRequest *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::ListStatus *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::OrderCancelRequestAndNewOrderSingle *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::LimitQuery *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::LimitResponse *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::OrderMassCancelRequest *msg) const
        {

        }

        bool BrokerRouterClient::operator() (const FIX8::BNB::OrderMassCancelReport *msg) const
        {

        }
        */
    }
}


