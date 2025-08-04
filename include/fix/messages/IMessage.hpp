#pragma once

#include <quickfix/Message.h>

class IMessage
{
public:
    virtual ~IMessage() = default;

    virtual FIX::Message& build()     {
        if (!order_) {
            throw std::runtime_error("Order not initialized.");
        }
        return *order_;
    }

protected:
    std::unique_ptr<FIX::Message> order_;
};
