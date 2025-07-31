
set(FIX_COMMON_LIBS
    quickfix
    quill::quill
)

add_executable(fixClient examples/fix/broker.cpp)
target_link_libraries(restClient ${FIX_COMMON_LIBS})
