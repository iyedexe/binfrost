cmake_minimum_required(VERSION 3.10)
project(fix_bnb)

include_directories(${CMAKE_SOURCE_DIR}/fix)

#   include_directories(${CMAKE_CURRENT_BINARY_DIR})
#   FIX8_GENERATE_CPP(FIX8_SRCS FIX8_HDRS /usr/share/fix8/schema/FIX42.xml)
#   add_executable(bar bar.cpp ${FIX8_SRCS} ${FIX8_HDRS})
#   target_link_libraries(bar ${FIX8_LIBRARIES} ${POCO_LIBRARIES} ${BerkeleyDB_CXX_LIBRARIES})

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_MODULE_PATH )
list(APPEND CMAKE_MODULE_PATH "/usr/local/share/fix8/contrib")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Fix8 REQUIRED)
find_package(Poco REQUIRED COMPONENTS Net Foundation)
find_package(Sodium REQUIRED)
find_package(Catch2 3 REQUIRED)

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
                                          