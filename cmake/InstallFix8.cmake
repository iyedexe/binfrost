
# Detect OS
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(FIX8_INSTALL_DIR "${CMAKE_BINARY_DIR}/fix8-install")

    if(NOT EXISTS "${FIX8_INSTALL_DIR}/lib")
        message(STATUS "Fetching and building FIX8 for Linux...")

        if(NOT EXISTS "${CMAKE_BINARY_DIR}/fix8")
            execute_process(
                COMMAND git clone --depth=1 https://github.com/fix8/fix8.git
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                RESULT_VARIABLE GIT_CLONE_RESULT
            )
            if(NOT GIT_CLONE_RESULT EQUAL 0)
                message(FATAL_ERROR "Failed to clone FIX8 repository")
            endif()
        else()
            message(STATUS "fix8 already cloned.")
        endif()

        execute_process(
            COMMAND ./bootstrap
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/fix8
            RESULT_VARIABLE BOOTSTRAP_RESULT
        )
        if(NOT BOOTSTRAP_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to bootstrap FIX8")
        endif()

        execute_process(
            COMMAND ./configure --prefix=${FIX8_INSTALL_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/fix8
            RESULT_VARIABLE CONFIGURE_RESULT
        )
        if(NOT CONFIGURE_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to configure FIX8")
        endif()

        execute_process(
            COMMAND make -j$(nproc)
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/fix8
            RESULT_VARIABLE MAKE_RESULT
        )
        if(NOT MAKE_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to build FIX8")
        endif()

        execute_process(
            COMMAND make install
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/fix8
            RESULT_VARIABLE INSTALL_RESULT
        )
        if(NOT INSTALL_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install FIX8")
        endif()
    endif()

    include_directories(${FIX8_INSTALL_DIR}/include)
    link_directories(${FIX8_INSTALL_DIR}/lib)
    add_library(fix8 STATIC IMPORTED)
    set_target_properties(fix8 PROPERTIES IMPORTED_LOCATION ${FIX8_INSTALL_DIR}/lib/libfix8.a)

elseif(WIN32)
    set(NUGET_PATH "${CMAKE_BINARY_DIR}/nuget.exe")
    set(NUGET_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/libs/nuget")

    if(NOT EXISTS ${NUGET_PATH})
        message(STATUS "Downloading NuGet...")
        file(DOWNLOAD 
            https://dist.nuget.org/win-x86-commandline/latest/nuget.exe 
            ${NUGET_PATH}
            SHOW_PROGRESS
        )
    endif()

    message(STATUS "Installing Fix8 using NuGet...")
    execute_process(
        COMMAND ${NUGET_PATH} install fix8.stable -Version 1.4.20191024.1 -OutputDirectory ${NUGET_OUTPUT_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE NUGET_RESULT
    )

    if(NUGET_RESULT AND NOT NUGET_RESULT EQUAL 0)
        message(FATAL_ERROR "Error: NuGet package installation failed.")
    endif()

    message(STATUS "Fix8 successfully installed via NuGet.")
    include_directories(${NUGET_OUTPUT_DIR}/fix8.stable.1.4.20191024.1/build/native/include)
    link_directories(${NUGET_OUTPUT_DIR}/fix8.stable.1.4.20191024.1/build/native/lib)
    add_library(fix8 STATIC IMPORTED)
    set_target_properties(fix8 PROPERTIES IMPORTED_LOCATION ${NUGET_OUTPUT_DIR}/fix8.stable.1.4.20191024.1/build/native/lib/fix8.lib)
endif()
