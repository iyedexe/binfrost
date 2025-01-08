#include "ws/requests/api/Account.hpp"

namespace BNB
{
    namespace WS
    {
        namespace Account
        {
            Information::Information() : method_("account.status") 
            {
                params_ = {
                    {"omitZeroBalances", "true"},
                };
            }

            std::string Information::dump() const
            {
                return RequestsBuilder::paramsSignedRequest(id_, method_, params_);
            }
        }
    }
    
}
