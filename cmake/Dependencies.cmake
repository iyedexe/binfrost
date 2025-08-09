message(STATUS "Dependencies handling ...")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/OE)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/MD)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-oe.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/OE/FIX44.xml
)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-md.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/MD/FIX44.xml
)

find_program(UV_EXECUTABLE uv)
if(NOT UV_EXECUTABLE)
    message(FATAL_ERROR "uv executable not found. Please ensure uv is installed and in your PATH.")
endif()

message(STATUS "Generating Feeder FIX classes...")
execute_process(
    COMMAND ${UV_EXECUTABLE} run ${CMAKE_CURRENT_SOURCE_DIR}/scripts/codegen.py
        --xml ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/MD/FIX44.xml
        --output ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/
        --name MD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE feeder_result
)
if(NOT feeder_result EQUAL 0)
    message(FATAL_ERROR "Feeder FIX code generation failed!")
endif()

message(STATUS "Generating Broker FIX classes...")
execute_process(
    COMMAND ${UV_EXECUTABLE} run ${CMAKE_CURRENT_SOURCE_DIR}/scripts/codegen.py
        --xml ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/OE/FIX44.xml
        --output ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/fix/
        --name OE
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE broker_result
)
if(NOT broker_result EQUAL 0)
    message(FATAL_ERROR "Broker FIX code generation failed!")
endif()
