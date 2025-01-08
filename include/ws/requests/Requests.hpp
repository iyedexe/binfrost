#pragma once
#include <string>
#include <map>
#include <nlohmann/json.hpp>

namespace BNB
{
    namespace WS
    {
        class IRequest {
        public:
            virtual std::string getId() const { return id_; }
            virtual std::string getMethod() const { return method_; }
            virtual std::map<std::string, std::string> getParams() const { return params_; }
            virtual std::string dump() const = 0;
        
        protected:
            std::string id_;
            std::string method_;
            std::map<std::string, std::string> params_;
        };
    }
}
