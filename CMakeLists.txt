cmake_minimum_required(VERSION 3.10)
project(fix_bnb)
set(CMAKE_CXX_STANDARD 20)

# warning for temolate class destructor c20 (webscoketpp)
# SET(C20_WARNING_TEMPLATE_CDTOR_MUTE "-Wno-template-id-cdtor")
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${C20_WARNING_TEMPLATE_CDTOR_MUTE}")

# useful for unwanted casts in json
set(JSON_ImplicitConversions OFF)

list(APPEND CMAKE_MODULE_PATH "/usr/local/share/fix8/contrib")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Enable CMake's built-in dependency managers
include(cmake/Dependencies.cmake)

# Add FIX8 code generation logic
include(cmake/GenerateFixCode.cmake)

# Generate FIX8 source files
GENERATE_SPOT_BNB_FIX(FIX8_SRCS FIX8_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/oe/broker.xml")
GENERATE_SPOT_BNB_FIX(FIX8_SRCS FIX8_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/md/feeder.xml")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/codegen)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files and targets
include(cmake/Targets.cmake)
