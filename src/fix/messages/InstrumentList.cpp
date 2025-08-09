#include "fix/messages/InstrumentList.hpp"
#include <quickfix/Group.h>

InstrumentList::InstrumentList(const std::string& requestId) {
    order_ = std::make_unique<FIX44::MD::InstrumentListRequest>();
    order_->setField(FIX::MD::InstrumentReqID(requestId));
    order_->setField(FIX::MD::InstrumentListRequestType(FIX::MD::InstrumentListRequestType_ALL_INSTRUMENTS));    
}

InstrumentList& InstrumentList::forSymbol(const std::string& symbol) {
    order_->setField(FIX::MD::InstrumentListRequestType(FIX::MD::InstrumentListRequestType_SINGLE_INSTRUMENT));    
    order_->setField(FIX::MD::Symbol(symbol));
    return *this;
}