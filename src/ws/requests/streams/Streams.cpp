#include "ws/requests/streams/Streams.hpp"

namespace BNB::WS::Streams
{
    Subscribe::Subscribe(const std::map<std::string, std::string>& streams) 
    {
        method_= "SUBSCRIBE";
        params_ = streams;
    }

    std::string Subscribe::dump() const
    {
        return RequestsBuilder::streamsRequest(id_, method_, params_);
    }
    
    Unsubscribe::Unsubscribe(const std::map<std::string, std::string>& streams) 
    {
        method_= "UNSUBSCRIBE";
        params_ = streams;
    }

    std::string Unsubscribe::dump() const
    {
        return RequestsBuilder::streamsRequest(id_, method_, params_);
    }

    ListSubscriptions::ListSubscriptions() 
    {
        method_= "LIST_SUBSCRIPTIONS";
    }

    std::string ListSubscriptions::dump() const
    {
        return RequestsBuilder::basicRequest(id_, method_);
    }

    SetProperty::SetProperty(const std::string& property, const std::string& value) 
    {
        method_= "SET_PROPERTY";
        params_ = {property, value};
    }

    std::string SetProperty::dump() const
    {
        return RequestsBuilder::paramsUnsignedRequest(id_, method_, params_);
    }
}
