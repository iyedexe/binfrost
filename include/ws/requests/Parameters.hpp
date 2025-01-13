#pragma once

#include "ws/requests/IRequests.hpp"

#include <vector>

namespace BNB::WS
{
    namespace ParamNames
    {
        constexpr std::string_view symbol = "symbol";
        constexpr std::string_view symbols = "symbols";
        constexpr std::string_view permissions = "permissions";
        constexpr std::string_view showPermissionSets = "showPermissionSets";
        constexpr std::string_view symbolStatus = "symbolStatus";
        constexpr std::string_view side = "side";
        constexpr std::string_view type = "type";
        constexpr std::string_view quantity = "quantity";
        constexpr std::string_view tradeStream = "trade";
        constexpr std::string_view userStream = "listenKey";

    }

    using Symbol = RequestParam<ParamNames::symbol, std::string>;
    using Symbols = RequestParam<ParamNames::symbols, std::vector<std::string>>;
    using Permissions = RequestParam<ParamNames::permissions, std::vector<std::string>>;
    using ShowPermissionSets = RequestParam<ParamNames::showPermissionSets, bool>;
    using SymbolStatus = RequestParam<ParamNames::symbolStatus, std::string>;
    using Side = RequestParam<ParamNames::side, std::string>;
    using Type = RequestParam<ParamNames::type, std::string>;
    using Quantity = RequestParam<ParamNames::quantity, double>;
    using TradeStream = RequestParam<ParamNames::tradeStream, std::string>;
    using UserStream = RequestParam<ParamNames::userStream, std::string>;
    

}
