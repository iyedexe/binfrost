function(GENERATE_SPOT_BNB_FIX SRCS HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: GENERATE_SPOT_BNB_FIX() called without any XML schema files")
    return()
  endif()
  message("Generating source files for FIX XML")

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
      COMMENT "Running C++ FIX8 compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)

endfunction()
