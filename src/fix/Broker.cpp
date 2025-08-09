#include "fix/Broker.hpp"
#include "logger.hpp"

namespace BNB::FIX
{
    void Broker::onMessage(const FIX44::OE::Heartbeat& message, const SessionID& sessionID)
    {
        LOG_WARNING("Received unhandled Heartbeat: [{}]", replaceSOHWithPipe(message.toString()));
    }

}
