#include "ws/requests/api/General.hpp"

namespace BNB::WS::General
{
    Ping::Ping()
    {
        method_= "ping";
    }
    std::string Ping::dump() const
    {
        return RequestsBuilder::basicRequest(id_, method_);
    }
    CheckServerTime::CheckServerTime()
    {
        method_= "time";
    }
    std::string CheckServerTime::dump() const
    {
        return RequestsBuilder::basicRequest(id_, method_);
    }
    ExchangeInfo::ExchangeInfo()
    {
        method_ = "exchangeInfo";
    }
    std::string ExchangeInfo::dump() const
    {
        return RequestsBuilder::paramsUnsignedRequest(id_, method_, params_);
    }
}