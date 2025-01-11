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

        nlohmann::json ApiClient::getResponseForId(const RequestId& id)
        {
            LOG_DEBUG("[API_CLIENT] Waiting for message id: [{}]", id);
            // may wait indefinitely for invalid id
            std::unique_lock<std::mutex> lock(responseMutex_);
            if (requestResponses_.find(id) != requestResponses_.end())
            {
                return requestResponses_[id];
            }
            responseCond_.wait(lock, [this, &id]() {
                return requestResponses_.find(id) != requestResponses_.end();
            });
            return requestResponses_[id];
        }
        
        nlohmann::json ApiClient::getLastUpdate()
        {
            // may wait indefinitely if not running
            std::unique_lock<std::mutex> lock(updateMutex_);
            updateCond_.wait(lock, [this] { return !updateQueue_.empty(); });

            nlohmann::json update = updateQueue_.front();
            updateQueue_.pop();
            return update;
        }

        void ApiClient::onMessage(websocketpp::connection_hdl hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg)
        {
            try {
                std::string payload = msg->get_payload();
                auto jsonData = nlohmann::json::parse(payload);

                // if response to a request
                if (jsonData.contains("id")) {
                    RequestId messageId = jsonData["id"];

                    if (pendingRequests_.count(messageId)) {
                        pendingRequests_.erase(messageId);
                        LOG_INFO("[STREAMS_CLIENT] Response received for request ID: {}", messageId);
                    }
                    {
                        std::lock_guard<std::mutex> lock(responseMutex_);
                        requestResponses_[messageId] = std::move(jsonData);
                    }                    
                    responseCond_.notify_all();
                    return;
                }
                // else response is an update
                {
                    std::lock_guard<std::mutex> lock(updateMutex_);
                    updateQueue_.push(std::move(jsonData));
                }
                updateCond_.notify_one();
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