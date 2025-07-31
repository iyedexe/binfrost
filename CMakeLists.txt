cmake_minimum_required(VERSION 3.30)

project(
  arthemis
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(JSON_ImplicitConversions OFF)


include(cmake/Dependencies.cmake)


find_package(Boost REQUIRED COMPONENTS asio beast uuid url)
include_directories(${Boost_INCLUDE_DIRS})
find_package(OpenSSL REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)
find_package(quill CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

#find_package(Catch2 REQUIRED)
#find_package(websocketpp REQUIRED)

find_package(quickfix REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(cmake/Targets.cmake)


