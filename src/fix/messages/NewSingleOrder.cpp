#include "fix/messages/NewSingleOrder.hpp"
#include <stdexcept>

NewSingleOrder::NewSingleOrder(const std::string &clOrdID, char ordType, char side, const std::string &symbol)
{
    order_ = std::make_unique<FIX44::NewOrderSingle>();
    order_->setField(FIX::ClOrdID(clOrdID));
    order_->setField(FIX::OrdType(ordType));
    order_->setField(FIX::Side(side));
    order_->setField(FIX::Symbol(symbol));
}

NewSingleOrder &&NewSingleOrder::orderQty(double qty)
{
    order_->setField(FIX::OrderQty(qty));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::execInst(std::string val)
{
    order_->setField(FIX::ExecInst(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::price(double val)
{
    order_->setField(FIX::Price(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::timeInForce(char val)
{
    order_->setField(FIX::TimeInForce(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::maxFloor(double val)
{
    order_->setField(FIX::MaxFloor(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::cashOrderQty(double val)
{
    order_->setField(FIX::CashOrderQty(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::targetStrategy(int val)
{
    if (val < 1000000)
        throw std::runtime_error("TargetStrategy must be >= 1000000");
    order_->setField(FIX::TargetStrategy(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::strategyID(int val)
{
    //    order_->setField(FIX::StrategyID(val));
    order_->setField(7940, std::to_string(val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::selfTradePreventionMode(char val)
{
    //    order_->setField(FIX::CharField(25001, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerType(char val)
{
    //    order_->setField(FIX::CharField(1100, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerAction(char val)
{
    //    order_->setField(FIX::CharField(1101, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerPrice(double val)
{
    //    order_->setField(FIX::PriceField(1102, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerPriceType(char val)
{
    //    order_->setField(FIX::CharField(1107, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerPriceDirection(char val)
{
    //    order_->setField(FIX::CharField(1109, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::triggerTrailingDeltaBips(int val)
{
    //    order_->setField(FIX::IntField(25009, val));
    return std::move(*this);
}

NewSingleOrder &&NewSingleOrder::sor(bool val)
{
    //    order_->setField(FIX::BoolField(25032, val));
    return std::move(*this);
}