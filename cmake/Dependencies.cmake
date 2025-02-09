
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

# Setup NuGet path
set(NUGET_PATH "${CMAKE_BINARY_DIR}/nuget.exe")

# Download NuGet if not already present
if(NOT EXISTS ${NUGET_PATH})
    message(STATUS "Downloading NuGet...")
    file(DOWNLOAD 
        https://dist.nuget.org/win-x86-commandline/latest/nuget.exe 
        ${NUGET_PATH}
        SHOW_PROGRESS
    )
endif()

# Install Fix8 package
message(STATUS "Installing Fix8 using NuGet...")

if(WIN32)
    execute_process(
        COMMAND ${NUGET_PATH} install fix8.stable -Version 1.4.20191024.1 -OutputDirectory ${CMAKE_SOURCE_DIR}/libs/nuget
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE NUGET_RESULT
    )
else()
    execute_process(
        COMMAND mono ${NUGET_PATH} install fix8.stable -Version 1.4.20191024.1 -OutputDirectory ${CMAKE_SOURCE_DIR}/libs/nuget
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE NUGET_RESULT
    )
endif()

# Handle errors
if(NUGET_RESULT AND NOT NUGET_RESULT EQUAL 0)
    message(FATAL_ERROR "Error: NuGet package installation failed.")
endif()

message(STATUS "Fix8 successfully installed via NuGet.")

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Poco REQUIRED COMPONENTS Net Foundation)
# find_package(Fix8 REQUIRED)
# add_subdirectory(${CMAKE_SOURCE_DIR}/libs/websocketpp)

find_package(Sodium REQUIRED)
find_package(Catch2 3 REQUIRED)

find_package(websocketpp REQUIRED)
find_package(quill REQUIRED)
find_package(nlohmann_json REQUIRED)
