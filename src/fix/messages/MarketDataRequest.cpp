#include "fix/messages/MarketDataRequest.hpp"
#include <quickfix/Group.h>

MarketDataRequest::MarketDataRequest(const std::string& requestId) {
    order_ = std::make_unique<FIX44::MD::MarketDataRequest>();
    order_->setField(FIX::MD::MDReqID(requestId));
    order_->setField(FIX::MD::SubscriptionRequestType('1'));
}

MarketDataRequest&& MarketDataRequest::forSymbol(const std::string& symbol) {
    FIX44::MD::MarketDataRequest::NoRelatedSym group;
    group.setField(FIX::MD::Symbol(symbol));
    order_->addGroup(group);
    return std::move(*this);
}

MarketDataRequest&& MarketDataRequest::subscribeToStream(StreamType stream) {

    switch (stream) {
        case StreamType::Trade: {
            FIX44::MD::MarketDataRequest::NoMDEntryTypes group;
            group.setField(FIX::MD::MDEntryType(FIX::MD::MDEntryType_TRADE));
            order_->addGroup(group);
            break;
        }
        case StreamType::BookTicker: {
            order_->setField(FIX::MarketDepth(1));
            FIX44::MD::MarketDataRequest::NoMDEntryTypes bidGroup;
            bidGroup.setField(FIX::MD::MDEntryType(FIX::MD::MDEntryType_BID));
            order_->addGroup(bidGroup);

            FIX44::MD::MarketDataRequest::NoMDEntryTypes offerGroup;
            offerGroup.setField(FIX::MD::MDEntryType(FIX::MD::MDEntryType_OFFER));
            order_->addGroup(offerGroup);
            break;
        }
        case StreamType::DiffDepth: {
            order_->setField(FIX::MarketDepth(5));
            FIX44::MD::MarketDataRequest::NoMDEntryTypes bidGroup;
            bidGroup.setField(FIX::MD::MDEntryType(FIX::MD::MDEntryType_BID));
            order_->addGroup(bidGroup);

            FIX44::MD::MarketDataRequest::NoMDEntryTypes offerGroup;
            offerGroup.setField(FIX::MD::MDEntryType(FIX::MD::MDEntryType_OFFER));
            order_->addGroup(offerGroup);
            break;
        }
    }

    return std::move(*this);
}

MarketDataRequest&& MarketDataRequest::setMarketDepth(int depth) {
    order_->setField(FIX::MD::MarketDepth(depth));
    return std::move(*this);
}
