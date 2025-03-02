
# Ensure required directories exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/oe)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/md)

# Download FIX schemas
file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-oe.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/oe/broker.xml
)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-md.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/md/feeder.xml
)

# -------------------- CHECK IF VCPKG IS INSTALLED --------------------

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Error: CMAKE_TOOLCHAIN_FILE not set, please do so by passing it to cmake.")
endif()

find_program(VCPKG_EXEC vcpkg)
if(NOT VCPKG_EXEC)
    message(FATAL_ERROR "Error: vcpkg not found! Please install vcpkg before proceeding.")
endif()

# Install dependencies with vcpkg (reads from vcpkg.json)
message(STATUS "Using vcpkg for dependency management...")

include(cmake/InstallFix8.cmake)