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
    }

    using Symbol = RequestParam<ParamNames::symbol, std::string>;
    using Symbols = RequestParam<ParamNames::symbols, std::vector<std::string>>;
    using Permissions = RequestParam<ParamNames::permissions, std::vector<std::string>>;
    using ShowPermissionSets = RequestParam<ParamNames::showPermissionSets, bool>;
    using SymbolStatus = RequestParam<ParamNames::symbolStatus, std::string>;

}
