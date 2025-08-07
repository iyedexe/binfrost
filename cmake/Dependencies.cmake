message(STATUS "Dependencies handling ...")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/OE)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/MD)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-oe.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/OE/FIX44.xml
)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-md.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/MD/FIX44.xml
)

find_program(UV_EXECUTABLE uv)
if(NOT UV_EXECUTABLE)
    message(FATAL_ERROR "uv executable not found. Please ensure uv is installed and in your PATH.")
endif()

# Define output files to check if they already exist
set(FEEDER_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/feeder/MessageCracker.hpp")
set(BROKER_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/broker/MessageCracker.hpp")

# Generate Feeder FIX classes during configuration
if(NOT EXISTS ${FEEDER_OUTPUT})
    message(STATUS "Generating Feeder FIX classes...")
    execute_process(
        COMMAND ${UV_EXECUTABLE} run python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/codegen.py
            --xml ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/MD/FIX44.xml
            --output ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/
            --name MD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE feeder_result
    )
    if(NOT feeder_result EQUAL 0)
        message(FATAL_ERROR "Feeder FIX code generation failed!")
    endif()
endif()

# Generate Broker FIX classes during configuration
if(NOT EXISTS ${BROKER_OUTPUT})
    message(STATUS "Generating Broker FIX classes...")
    execute_process(
        COMMAND ${UV_EXECUTABLE} run python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/codegen.py
            --xml ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/OE/FIX44.xml
            --output ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/
            --name OE
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE broker_result
    )
    if(NOT broker_result EQUAL 0)
        message(FATAL_ERROR "Broker FIX code generation failed!")
    endif()
endif()
