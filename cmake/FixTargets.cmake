
set(FIX_COMMON_LIBS
    quickfix
    quill::quill
)

set(FIX_BROKER_SOURCES
    src/fix/FixApplication.cpp
    src/fix/Client.cpp
    src/fix/MessageBuilder.cpp
    src/fix/messages/NewSingleOrder.cpp
    ${CRYPTO_UTILS_SOURCES}
)

add_executable(fixBroker examples/fix/broker.cpp ${FIX_BROKER_SOURCES})
target_link_libraries(fixBroker ${FIX_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})


set(FIX_FEEDER_SOURCES
    src/fix/FixApplication.cpp
    src/fix/Client.cpp
    src/fix/Feeder.cpp
    src/fix/MessageBuilder.cpp
    src/fix/messages/MarketDataRequest.cpp
    ${CRYPTO_UTILS_SOURCES}
)

add_executable(fixFeeder examples/fix/feeder.cpp ${FIX_FEEDER_SOURCES})
target_link_libraries(fixFeeder ${FIX_COMMON_LIBS} ${CRYPTO_UTILS_LIBS})