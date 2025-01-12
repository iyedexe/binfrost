#pragma once
#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "logger.hpp"

namespace BNB::WS
{
    template <const std::string_view& Name, typename T>
    class RequestParam {
    public:
        explicit RequestParam(const T& value) : value_(value) {}

        const std::string_view getName() const { return Name; }
        const T& getValue() const { return value_; }

    private:
        T value_;
    };

    class IRequest {
    public:
        IRequest() {
            id_ = generateRequestId();
        }
        virtual ~IRequest() = default;
        virtual std::string getId() const { return id_; }
        virtual std::string getMethod() const { return method_; }
        virtual std::string dump() const = 0;

        template <const std::string_view& Name, typename T>
        IRequest& operator<<(const RequestParam<Name, T>& p) {
            params_.emplace(p.getName(), p.getValue());

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
        nlohmann::json params_;
    };
}
