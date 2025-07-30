
set(REST_COMMON_LIBS
    Boost::beast
    Boost::asio
    Boost::uuid
    quill::quill
)

set(REST_CLIENT_SOURCES
    ${CRYPTO_UTILS_SOURCES}
    src/rest/ApiClient.cpp
    src/rest/requests/UserStream.cpp
    src/rest/requests/RequestsBuilder.cpp
)

add_executable(restClient examples/rest/client.cpp ${REST_CLIENT_SOURCES})
target_link_libraries(restClient ${REST_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})
