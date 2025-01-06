cmake_minimum_required(VERSION 3.10)
project(fix_bnb)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "/usr/local/share/fix8/contrib")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Fix8 REQUIRED)
find_package(Poco REQUIRED COMPONENTS Net Foundation)
find_package(Sodium REQUIRED)
find_package(Catch2 3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/fix)

file(GLOB_RECURSE BNBFIXCLIENTSOURCES "fix/*.cpp")

set(COMMON_SOURCES
    ${BNBFIXCLIENTSOURCES}
    src/broker.cpp
)
add_executable(broker ${COMMON_SOURCES})
target_link_libraries(broker ${FIX8_LIBRARIES} ${Poco_LIBRARIES} sodium PocoNetSSL)

set(TEST_SOURCES
    ${BNBFIXCLIENTSOURCES}
    tests/encodingTest.cpp
    tests/logonMessageTest.cpp
)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain  ${FIX8_LIBRARIES} ${Poco_LIBRARIES} sodium PocoNetSSL)
                                          