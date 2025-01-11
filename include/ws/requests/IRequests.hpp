#pragma once
#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


namespace BNB::WS
{
    template <typename T= std::string>
    class IRequest {
    public:
        IRequest() {
            id_ = generateRequestId();
        }
        virtual ~IRequest() = default;
        virtual std::string getId() const { return id_; }
        virtual std::string getMethod() const { return method_; }
        virtual std::map<std::string, T> getParams() const { return params_; }
        virtual std::string dump() const = 0;

        IRequest& operator<<(const std::pair<std::string, T>& keyValuePair) {
            params_[keyValuePair.first] = keyValuePair.second;
            return *this;
        }

    protected:
        std::string generateRequestId() {
            boost::uuids::uuid uuid = boost::uuids::random_generator()();
            std::string requestId = boost::uuids::to_string(uuid);
            return requestId;
        }
        
        std::string id_;
        std::string method_;
        std::map<std::string, T> params_;
    };
}
