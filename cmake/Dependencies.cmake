message(STATUS "Dependencies handling ...")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/feeder)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/broker)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-oe.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/broker/FIX44.xml
)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-md.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/feeder/FIX44.xml
)

find_program(UV_EXECUTABLE uv)
if(NOT UV_EXECUTABLE)
    message(FATAL_ERROR "uv executable not found. Please ensure uv is installed and in your PATH.")
endif()

add_custom_target(codegen ALL
    COMMAND ${UV_EXECUTABLE} run python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/codegen.py
        --xml ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/feeder/FIX44.xml
        --output ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/
        --name feeder
    COMMAND ${UV_EXECUTABLE} run python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/codegen.py
        --xml ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/broker/FIX44.xml
        --output ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/
        --name broker
    COMMENT "Running cracker.py on FIX XML files using uv + Python..."
    VERBATIM
)
