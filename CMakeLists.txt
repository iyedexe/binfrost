cmake_minimum_required(VERSION 3.10)
project(fix_bnb)
set(CMAKE_CXX_STANDARD 20)




list(APPEND CMAKE_MODULE_PATH "/usr/local/share/fix8/contrib")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Fix8 REQUIRED)
find_package(Poco REQUIRED COMPONENTS Net Foundation)
find_package(Sodium REQUIRED)
find_package(Catch2 3 REQUIRED)


function(GENERATE_SPOT_BNB_FIX SRCS HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: GENERATE_SPOT_BNB_FIX() called without any XML schema files")
    return()
  endif()

  set(${SRCS})
  set(${HDRS})

  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    get_filename_component(FIL_DIR ${FIL} DIRECTORY)

    list(APPEND ${SRCS}
        "${FIL_DIR}/${FIL_WE}_classes.cpp"
        "${FIL_DIR}/${FIL_WE}_traits.cpp"
        "${FIL_DIR}/${FIL_WE}_types.cpp")
    list(APPEND ${HDRS}
        "${FIL_DIR}/${FIL_WE}_classes.hpp"
        "${FIL_DIR}/${FIL_WE}_router.hpp"
        "${FIL_DIR}/${FIL_WE}_types.hpp")

    add_custom_command(
      OUTPUT "${FIL_DIR}/${FIL_WE}_classes.cpp"
             "${FIL_DIR}/${FIL_WE}_classes.hpp"
             "${FIL_DIR}/${FIL_WE}_router.hpp"
             "${FIL_DIR}/${FIL_WE}_traits.cpp"
             "${FIL_DIR}/${FIL_WE}_types.cpp"
             "${FIL_DIR}/${FIL_WE}_types.hpp"
      COMMAND  ${FIX8_COMPILER}
      ARGS -o ${FIL_DIR} -p ${FIL_WE} -n BNB ${ABS_FIL}
      DEPENDS ${ABS_FIL}
      COMMENT "Running C++ fix8 compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)

endfunction()

GENERATE_SPOT_BNB_FIX(FIX8_SRCS FIX8_HDRS "${CMAKE_SOURCE_DIR}/fix/bnb/oe/broker.xml")

include_directories(${CMAKE_SOURCE_DIR}/fix)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(COMMON_SOURCES
    ${FIX8_SRCS}
    ${FIX8_HDRS}
    src/BrokerSessionClient.cpp
    src/BrokerRouterClient.cpp
)
add_executable(broker src/broker.cpp ${COMMON_SOURCES})
target_include_directories(broker PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(broker ${FIX8_LIBRARIES} ${Poco_LIBRARIES} sodium PocoNetSSL)

set(TEST_SOURCES
    ${COMMON_SOURCES}
    tests/encodingTest.cpp
    tests/logonMessageTest.cpp
)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain  ${FIX8_LIBRARIES} ${Poco_LIBRARIES} sodium PocoNetSSL)
                                          