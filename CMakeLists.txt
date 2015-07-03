# SIGA QT - MAIN CMAKE FILE

# Specify cmake version compatibility that will be used
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

# Set project and it's name
set(PROJECT_NAME "siga")
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED m64)
    message(FATAL_ERROR "ERROR: System architeture is mandatory! Use -Dm64=TRUE/FALSE")
elseif((NOT ${m64} STREQUAL TRUE) AND (NOT ${m64} STREQUAL FALSE))
    message(FATAL_ERROR "ERROR: Use -Dm64=TRUE/FALSE")
endif()

# Set current platform
message(STATUS "> Identifying platform...")

if(WINDOWS OR WIN32)
    set(platform "win")
	
	if(NOT DEFINED vs_compiler_path)
		message(FATAL_ERROR "ERROR: you need to pass the visual studio 2013 compiler bin path. (Ex: -Dvs_compiler_path=C:/Program Files (x86)/Microsoft Visual Studio 12.0/VC/bin")
	endif()
	
	if(NOT DEFINED qt_path)
		message(FATAL_ERROR "ERROR: you need to specify qt path! (Ex: -Dqt_path=C:\Qt\5.3\msvc2013_64_opengl)\\")
	endif()
	
	if(${m64} STREQUAL TRUE)
		set(vs_compiler_path "${vs_compiler_path}/amd64/")
	else()
		set(vs_compiler_path "${vs_compiler_path}/amd64_x86/")
	endif()
	
	set(CMAKE_PREFIX_PATH "${qt_path}")
	
	set(cxx_compiler "${vs_compiler_path}cl.exe")
        set(compiler_flags "/EHsc")

        set(gtest_force_shared_crt ON CACHE BOOL “Use shared (DLL) run-time lib (CRT) even when Google Test is built as static lib.”)
	
elseif(APPLE)
    set(platform "mac")

elseif(UNIX)
    # get linux distro
    if(EXISTS "/etc/issue")
        file(READ "/etc/issue" contents)
        string(TOLOWER ${contents} contents)

        if(${contents} MATCHES "ubuntu")
            set(platform "ubuntu")

        elseif(${contents} MATCHES "debian")
            set(platform "debian")

        elseif(${contents} MATCHES "RedHat")
            set(platform "redhat")

        else()
            message(FATAL_ERROR "This linux distro (${contents}) is not supported!\nSupported distros are: Ubuntu, Debian and Red Hat.")
        endif()
		
		set(cxx_compiler "g++")
		set(compiler_flags "-std=c++11 -Wall -Wextra")

   else(EXISTS "/etc/issue")
        message(FATAL_ERROR "Platform not supported! The platforms supporteds are: Windows 7 and below, Ubuntu, Red Hat, Debian and Mac")
   endif(EXISTS "/etc/issue")

endif(WINDOWS OR WIN32)

if(${m64} STREQUAL "TRUE")
    set(system_architeture 64)
else()
    set(system_architeture 32)
endif()

set(platform "${platform}_x${system_architeture}")
message(STATUS "> Platform: ${platform}\n")

# Set the library and executable directories for the binary tree
if(${CMAKE_BUILD_TYPE} MATCHES "RELEASE" )
    set( EXECUTABLE_OUTPUT_PATH" ${CMAKE_CURRENT_LIST_DIR}/Build/Release/${platform}" )
    set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/Build/Release/${platform}/lib" )
else(${CMAKE_BUILD_TYPE} MATCHES "RELEASE" )
    set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/Build/Debug/${platform}" )
    set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/Build/Debug/${platform}/lib" )
endif()

# TODO: Set the compiler for mac
# Set C++ compiler and specify to use c++11
set(CMAKE_CXX_COMPILER CACHE ${cxx_compiler} FORCE)
set(CMAKE_CXX_FLAGS "${compiler_flags} ${CMAKE_CXX_FLAGS}")
		
# Find QT5 package
find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core LinguistTools OpenGL)

# include custom functions
include(cmake/functions.cmake)

# Initializing gmock
include(cmake/gmock_init.cmake)

# Set application version
include(CMakeProjectVersion.txt)

configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_SOURCE_DIR}/version.h"
)

# Add the current directory and unit tests directories to the list of paths to search for a file
include_directories(
    "."
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

# Set translation's languages
set(translation_languages pt_BR en_US de_DE)

get_target_property(QtLupdateLocation Qt5::lupdate LOCATION)
get_target_property(QtLreleaseLocation Qt5::lrelease LOCATION)
get_target_property(QtUIC_Location Qt5::uic LOCATION)

# Add subdirectories
add_subdirectory(core)
add_subdirectory(front)
add_subdirectory(third_party)
add_subdirectory(unit_tests)
add_subdirectory(utils)
add_subdirectory(view)

# Generate QM files
set(language_path ${EXECUTABLE_OUTPUT_PATH}/lang)

# Create the language path if it doesn't exist
if (NOT EXISTS ${language_path})
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${language_path}
    )
endif(NOT EXISTS ${language_path})

set(qm_file_list "")

foreach (language ${translation_languages})
    FILE(GLOB_RECURSE language_ts_files "*_${language}.ts")

    message(STATUS ${language_ts_files})

    set(qm_file "translation_package_${language}.qm")
    LIST(APPEND qm_file_list ${qm_file})

    add_custom_command(
                        OUTPUT "translation_package_${language}.qm"
                        COMMAND ${QtLreleaseLocation} ARGS ${language_ts_files} -qm ${language_path}/${qm_file}
                       )

endforeach(language ${translation_languages})

add_custom_target(run ALL DEPENDS ${qm_file_list})
