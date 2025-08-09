#pragma once

#include "codegen/fix/MD/fix44/InstrumentListRequest.hpp"
#include "codegen/fix/MD/FixValues.h"
#include "IMessage.hpp"
#include <string>


class InstrumentList : public IMessage {
public:
    explicit InstrumentList(const std::string& requestId);

    InstrumentList& forSymbol(const std::string& symbol);
};
