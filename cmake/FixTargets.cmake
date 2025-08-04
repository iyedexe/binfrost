
set(FIX_COMMON_LIBS
    quickfix
    quill::quill
)

set(FIX_CLIENT_SOURCES
    src/fix/FixApplication.cpp
    src/fix/FixClient.cpp
    src/fix/MessageBuilder.cpp
    src/fix/messages/NewSingleOrder.cpp
    ${CRYPTO_UTILS_SOURCES}
)

add_executable(fixClient examples/fix/broker.cpp ${FIX_CLIENT_SOURCES})
target_link_libraries(fixClient ${FIX_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})