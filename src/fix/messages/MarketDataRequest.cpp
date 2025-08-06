#include "fix/messages/MarketDataRequest.hpp"
#include <quickfix/Group.h>

MarketDataRequest::MarketDataRequest(const std::string& requestId) {
    order_ = std::make_unique<FIX44::MarketDataRequest>();
    order_->setField(FIX::MDReqID(requestId));
    order_->setField(FIX::SubscriptionRequestType('1'));
}

MarketDataRequest&& MarketDataRequest::forSymbol(const std::string& symbol) {
    FIX44::MarketDataRequest::NoRelatedSym group;
    group.setField(FIX::Symbol(symbol));
    order_->addGroup(group);
    return std::move(*this);
}

MarketDataRequest&& MarketDataRequest::subscribeToStream(StreamType stream) {

    switch (stream) {
        case StreamType::Trade: {
            FIX44::MarketDataRequest::NoMDEntryTypes group;
            group.setField(FIX::MDEntryType(FIX::MDEntryType_TRADE));
            order_->addGroup(group);
            break;
        }
        case StreamType::BookTicker: {
            order_->setField(FIX::MarketDepth(1));
            FIX44::MarketDataRequest::NoMDEntryTypes bidGroup;
            bidGroup.setField(FIX::MDEntryType(FIX::MDEntryType_BID));
            order_->addGroup(bidGroup);

            FIX44::MarketDataRequest::NoMDEntryTypes offerGroup;
            offerGroup.setField(FIX::MDEntryType(FIX::MDEntryType_OFFER));
            order_->addGroup(offerGroup);
            break;
        }
        case StreamType::DiffDepth: {
            order_->setField(FIX::MarketDepth(5));
            FIX44::MarketDataRequest::NoMDEntryTypes bidGroup;
            bidGroup.setField(FIX::MDEntryType(FIX::MDEntryType_BID));
            order_->addGroup(bidGroup);

            FIX44::MarketDataRequest::NoMDEntryTypes offerGroup;
            offerGroup.setField(FIX::MDEntryType(FIX::MDEntryType_OFFER));
            order_->addGroup(offerGroup);
            break;
        }
    }

    return std::move(*this);
}

MarketDataRequest&& MarketDataRequest::setMarketDepth(int depth) {
    order_->setField(FIX::MarketDepth(depth));
    return std::move(*this);
}
