#pragma once

#include <string>

#include <quickfix/fix44/NewOrderSingle.h>

#include "IMessage.hpp"

class NewSingleOrder : public IMessage
{
public:
    NewSingleOrder(const std::string &clOrdID, char ordType, char side, const std::string &symbol);

    NewSingleOrder &&orderQty(double qty);
    NewSingleOrder &&execInst(std::string val);
    NewSingleOrder &&price(double val);
    NewSingleOrder &&timeInForce(char val);
    NewSingleOrder &&maxFloor(double val);
    NewSingleOrder &&cashOrderQty(double val);
    NewSingleOrder &&targetStrategy(int val);
    NewSingleOrder &&strategyID(int val);
    NewSingleOrder &&selfTradePreventionMode(char val);
    NewSingleOrder &&triggerType(char val);
    NewSingleOrder &&triggerAction(char val);
    NewSingleOrder &&triggerPrice(double val);
    NewSingleOrder &&triggerPriceType(char val);
    NewSingleOrder &&triggerPriceDirection(char val);
    NewSingleOrder &&triggerTrailingDeltaBips(int val);
    NewSingleOrder &&sor(bool val);

};
