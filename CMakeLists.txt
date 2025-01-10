cmake_minimum_required(VERSION 3.10)
project(fix_bnb)
set(CMAKE_CXX_STANDARD 20)

# warning for temolate class destructor c20 (webscoketpp)
SET(C20_WARNING_TEMPLATE_CDTOR_MUTE "-Wno-template-id-cdtor")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${C20_WARNING_TEMPLATE_CDTOR_MUTE}")

# useful for unwanted casts in json
set(JSON_ImplicitConversions OFF)

list(APPEND CMAKE_MODULE_PATH "/usr/local/share/fix8/contrib")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost REQUIRED)
find_package(Fix8 REQUIRED)
find_package(Poco REQUIRED COMPONENTS Net Foundation)
find_package(Sodium REQUIRED)
find_package(Catch2 3 REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/websocketpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/quill)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/json)

function(GENERATE_SPOT_BNB_FIX SRCS HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: GENERATE_SPOT_BNB_FIX() called without any XML schema files")
    return()
  endif()

  set(${SRCS})
  set(${HDRS})

  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    get_filename_component(FIL_DIR ${FIL} DIRECTORY)

    list(APPEND ${SRCS}
        "${FIL_DIR}/${FIL_WE}_classes.cpp"
        "${FIL_DIR}/${FIL_WE}_traits.cpp"
        "${FIL_DIR}/${FIL_WE}_types.cpp")
    list(APPEND ${HDRS}
        "${FIL_DIR}/${FIL_WE}_classes.hpp"
        "${FIL_DIR}/${FIL_WE}_router.hpp"
        "${FIL_DIR}/${FIL_WE}_types.hpp")

    add_custom_command(
      OUTPUT "${FIL_DIR}/${FIL_WE}_classes.cpp"
             "${FIL_DIR}/${FIL_WE}_classes.hpp"
             "${FIL_DIR}/${FIL_WE}_router.hpp"
             "${FIL_DIR}/${FIL_WE}_traits.cpp"
             "${FIL_DIR}/${FIL_WE}_types.cpp"
             "${FIL_DIR}/${FIL_WE}_types.hpp"
      COMMAND  ${FIX8_COMPILER}
      ARGS -o ${FIL_DIR} -p ${FIL_WE} -n BNB ${ABS_FIL}
      DEPENDS ${ABS_FIL}
      COMMENT "Running C++ fix8 compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)

endfunction()

GENERATE_SPOT_BNB_FIX(FIX8_SRCS FIX8_HDRS "${CMAKE_SOURCE_DIR}/fix/bnb/oe/broker.xml")

include_directories(${CMAKE_SOURCE_DIR}/fix)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/websocketpp)
include_directories(${CMAKE_SOURCE_DIR}/libs/websocketpp/asio)
include_directories(${CMAKE_SOURCE_DIR}/libs/quill)
include_directories(${CMAKE_SOURCE_DIR}/libs/json/single_include)

set(FIX_COMMON_SOURCES
    ${FIX8_SRCS}
    ${FIX8_HDRS}
    src/fix/BrokerSessionClient.cpp
    src/fix/BrokerRouterClient.cpp
)
add_executable(fixBroker examples/fix/broker.cpp ${FIX_COMMON_SOURCES})
target_include_directories(fixBroker PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(fixBroker ${FIX8_LIBRARIES} ${Poco_LIBRARIES} sodium PocoNetSSL)


set(WS_COMMON_LIBS
    ${Boost_LIBRARIES}
    quill::quill
)
set(CRYPTO_UTILS_LIBS
    OpenSSL::SSL
    OpenSSL::Crypto
    sodium
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
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain  ${FIX8_LIBRARIES} ${Poco_LIBRARIES} sodium PocoNetSSL)
                        