#pragma once

#include "codegen/fix/MD/fix44/MarketDataRequest.hpp"
#include "codegen/fix/MD/FixValues.h"
#include "IMessage.hpp"
#include <string>
#include <memory>

enum class StreamType {
    Trade,
    BookTicker,
    DiffDepth
};


class MarketDataRequest : public IMessage {
public:
    explicit MarketDataRequest(const std::string& requestId);

    MarketDataRequest&& forSymbol(const std::string& symbol);
    MarketDataRequest&& subscribeToStream(StreamType stream);
    MarketDataRequest&& setMarketDepth(int depth);
};
