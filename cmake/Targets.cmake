message(STATUS "Building targets ...")

set(WS_COMMON_LIBS
    ${Boost_LIBRARIES}
    quill::quill
)

set(CRYPTO_UTILS_LIBS
    OpenSSL::SSL
    OpenSSL::Crypto
    unofficial-sodium::sodium
)

set(CRYPTO_UTILS_SOURCES
    src/crypto/ed25519.cpp
    src/crypto/hmac.cpp
    src/crypto/rsa.cpp
)

set(WS_COMMON_SOURCES
    src/ws/WebSocketListener.cpp
    src/ws/ApiClient.cpp
    src/ws/requests/RequestsBuilder.cpp
)

set(WS_FEEDER_SOURCES
    ${WS_COMMON_SOURCES}
    src/ws/requests/streams/Streams.cpp
)

set(REST_CLIENT_SOURCES
    ${CRYPTO_UTILS_SOURCES}
    src/rest/ApiClient.cpp
    src/rest/requests/UserStream.cpp
    src/rest/requests/RequestsBuilder.cpp
)

set(WS_BROKER_SOURCES
    ${WS_COMMON_SOURCES}
    ${CRYPTO_UTILS_SOURCES}
    src/ws/requests/api/Account.cpp
    src/ws/requests/api/General.cpp
    src/ws/requests/api/Trading.cpp
)

set(TEST_SOURCES
    ${FIX_COMMON_SOURCES}
    tests/encodingTest.cpp
    tests/logonMessageTest.cpp
)

add_executable(wsMarketFeeder examples/ws/market_data_feeder.cpp ${WS_FEEDER_SOURCES})
target_link_libraries(wsMarketFeeder ${WS_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})

add_executable(wsUserFeeder examples/ws/user_streams_feeder.cpp ${WS_FEEDER_SOURCES} ${REST_CLIENT_SOURCES})
target_link_libraries(wsUserFeeder ${WS_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})

add_executable(wsBroker examples/ws/broker.cpp ${WS_BROKER_SOURCES})
target_link_libraries(wsBroker ${WS_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})

add_executable(restClient examples/rest/client.cpp ${REST_CLIENT_SOURCES})
target_link_libraries(restClient ${WS_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${FIX8_LIBRARIES} ${CRYPTO_UTILS_LIBS})
