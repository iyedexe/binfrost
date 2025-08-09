#include "fix/messages/NewSingleOrder.hpp"
#include <stdexcept>

NewSingleOrder::NewSingleOrder(const std::string &clOrdID, char ordType, char side, const std::string &symbol)
{
    order_ = std::make_unique<FIX44::OE::NewOrderSingle>();
    order_->setField(FIX::OE::ClOrdID(clOrdID));
    order_->setField(FIX::OE::OrdType(ordType));
    order_->setField(FIX::OE::Side(side));
    order_->setField(FIX::OE::Symbol(symbol));
}

NewSingleOrder &&NewSingleOrder::orderQty(double qty)
{
    order_->setField(FIX::OE::OrderQty(qty));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::execInst(char val)
{
    order_->setField(FIX::OE::ExecInst(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::price(double val)
{
    order_->setField(FIX::OE::Price(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::timeInForce(char val)
{
    order_->setField(FIX::OE::TimeInForce(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::maxFloor(double val)
{
    order_->setField(FIX::OE::MaxFloor(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::cashOrderQty(double val)
{
    order_->setField(FIX::OE::CashOrderQty(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::targetStrategy(int val)
{
    if (val < 1000000)
        throw std::runtime_error("TargetStrategy must be >= 1000000");
    order_->setField(FIX::OE::TargetStrategy(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::strategyID(int val)
{
    order_->setField(FIX::OE::StrategyID(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::selfTradePreventionMode(char val)
{
    order_->setField(FIX::OE::SelfTradePreventionMode(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerType(char val)
{
    order_->setField(FIX::OE::TriggerType(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerAction(char val)
{
    order_->setField(FIX::OE::TriggerAction(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerPrice(double val)
{
    order_->setField(FIX::OE::TriggerPrice(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerPriceType(char val)
{
    order_->setField(FIX::OE::TriggerPriceType(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerPriceDirection(char val)
{
    order_->setField(FIX::OE::TriggerPriceDirection(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerTrailingDeltaBips(int val)
{
    order_->setField(FIX::OE::TriggerTrailingDeltaBips(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::sor(bool val)
{
    order_->setField(FIX::OE::SOR(val));
    return std::move(*this);
}