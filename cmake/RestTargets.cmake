
set(REST_COMMON_LIBS
    Boost::beast
    Boost::asio
    Boost::uuid
    Boost::url
    quill::quill
)

set(REST_CLIENT_SOURCES
    ${CRYPTO_UTILS_SOURCES}
    src/rest/ApiClient.cpp
    src/rest/requests/UserStream.cpp
    src/rest/requests/endpoints/General.cpp
    src/rest/requests/endpoints/MarketData.cpp
    src/rest/requests/RequestsBuilder.cpp
)


set(OPENSSL_CONF_PATH "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/etc/ssl/openssl.cnf")
message(STATUS "OPENSSL_CONF_PATH -> ${OPENSSL_CONF_PATH}")

add_executable(restClient examples/rest/client.cpp ${REST_CLIENT_SOURCES})
target_link_libraries(restClient ${REST_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})
target_compile_definitions(restClient PRIVATE OPENSSL_CONF_PATH=\"${OPENSSL_CONF_PATH}\")
