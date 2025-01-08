#include "ws/ApiClient.hpp"
#include "logger.hpp"

namespace BNB
{
    namespace WS
    {
        ApiClient::ApiClient(const std::string& wsEndpoint) : wsEndpoint_(wsEndpoint) {}

        ApiClient::~ApiClient() {}

        void ApiClient::start()
        {
            connect(wsEndpoint_);
            startClient();
        }

        void ApiClient::stop()
        {
            stopClient();
        }
        
        RequestId ApiClient::sendRequest(const IRequest& request)
        {
            writeWS(request.dump());
            RequestId requestId = request.getId();
            pendingRequests_.insert(requestId);
            return requestId;
        }

        void ApiClient::onMessage(websocketpp::connection_hdl hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg)
        {
            try {
                std::string payload = msg->get_payload();
                LOG_DEBUG("[STREAMS_CLIENT] onMessage: {}", payload);

                auto jsonData = nlohmann::json::parse(payload);

                // if response to a request
                if (jsonData.contains("id")) {
                    RequestId messageId = jsonData["id"];

                    if (pendingRequests_.count(messageId)) {
                        pendingRequests_.erase(messageId);
                        LOG_INFO("[STREAMS_CLIENT] Response received for request ID: {}", messageId);

                        if (jsonData.contains("error")) {
                            auto error_data = jsonData["error"];
                            int error_code = error_data.value("code", 0);
                            std::string error_msg = error_data.value("msg", "Unknown error");

                            LOG_ERROR("[STREAMS_CLIENT] Error received - Code: {}, Message: {}", error_code, error_msg);
                        }

                        // // Additional processing for the response if needed
                        // if (json_data.contains("result") && json_data["result"].is_null()) {
                        //     LOG_INFO("[FEEDER] Subscription to stream was successful.");
                        // } else {
                        //     LOG_WARNING("[FEEDER] Unexpected result in subscription response: {}", payload);
                        // }

                        return;
                    }
                }
            } catch (const std::exception& e) {
                LOG_ERROR("[FEEDER] onMessage error: {}", e.what());
            }            
        }
        
        void ApiClient::onClose(websocketpp::connection_hdl hdl)
        {
            WebSocketListener::onClose(hdl);
        }
        void ApiClient::onFail(websocketpp::connection_hdl hdl)
        {
            WebSocketListener::onFail(hdl);
        }
    }
}