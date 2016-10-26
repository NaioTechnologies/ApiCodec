#===================================================================================================
#
#	CMake file for building vitals
#
#===================================================================================================

#---------------------------------------------------------------------------------------------------
#
#	CMake compatibility
#
cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

project( apicodec )

enable_testing()

#---------------------------------------------------------------------------------------------------
#
#	Target name
#
include( ${PROJECT_SOURCE_DIR}/modules/Helpers.cmake )

#---------------------------------------------------------------------------------------------------
#
#   Module finding
#
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules )

#---------------------------------------------------------------------------------------------------
#
#	Warning Options / C++ Language Options / Code Generation Options
#
set( CMAKE_C_FLAGS "-fsigned-char -fdiagnostics-color" )

set( CMAKE_CXX_FLAGS "-W -Wall -Werror -std=c++14 -Wextra -Winline -Wc++11-compat -Wconversion \
	-Wconversion-null -Wsign-conversion -Wctor-dtor-privacy -Wdelete-non-virtual-dtor -Wnarrowing \
	-Wnon-virtual-dtor -Wreorder -Wshadow -Woverloaded-virtual -Wno-pmf-conversions -Wsign-promo \
	-Wcast-align -Wmissing-declarations -Woverlength-strings -Wunreachable-code \
	-fconstexpr-depth=10 -fno-elide-constructors -ffor-scope -fno-gnu-keywords \
	-ftemplate-backtrace-limit=10 -fuse-cxa-atexit -fexceptions -fsigned-char -fdiagnostics-color" )

#---------------------------------------------------------------------------------------------------
#
#	Compilers specific options
#
if( USE_CLANG )
    set( CMAKE_C_COMPILER "/usr/bin/clang" )
    set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
    add_compile_options( -Wno-c++98-compat -Wno-c++11-compat )
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.9" )
        message( FATAL_ERROR "Insufficient gcc version ; should be >= 4.9" )
    endif()
endif()

#--------------------------------------------------------------------------------------------------
#
#   Project options
#
option( BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON )
option( INSTALL_DOC "Set to OFF to skip build/install Documentation" OFF )

if( BUILD_SHARED_LIBS )
    set( CMAKE_FIND_LIBRARY_SUFFIXES ".so" )
else()
    set( CMAKE_FIND_LIBRARY_SUFFIXES ".a" )
endif()

#---------------------------------------------------------------------------------------------------
#
#   Source & Include directories
#
list_cpp_source_files( SOURCE_FILES src )

if( BUILD_SHARED_LIBS )
    add_library( lib${PROJECT_NAME} SHARED ${SOURCE_FILES} )
else()
    add_library( lib${PROJECT_NAME} STATIC ${SOURCE_FILES} )
endif()


#---------------------------------------------------------------------------------------------------
#
#   Target include folders
#
target_include_directories( lib${PROJECT_NAME} PUBLIC src )

#---------------------------------------------------------------------------------------------------
#
#   External libraries include folders
#
#target_include_directories( lib${PROJECT_NAME} SYSTEM PUBLIC )

#---------------------------------------------------------------------------------------------------
#
#   Target specific definitions
#
add_definitions( -fPIC -DDECL_SPEC )

#---------------------------------------------------------------------------------------------------
#
#   Target linking
#
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    if( WITH_SANITIZERS )
        target_link_libraries( lib${PROJECT_NAME} -lasan -lubsan -llsan  -lSDL_ttf -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_gfx )
    endif( WITH_SANITIZERS )
endif()

target_link_libraries( lib${PROJECT_NAME} )

#---------------------------------------------------------------------------------------------------
#
#   Library version
#
file( READ src/BuildVersion.hpp LIB_VERSION )

string( REGEX MATCH "define[ \t]+LIBRARY_MAJOR_VERSION[ \t]+([0-9]+)+"
        LIBRARY_MAJOR_VERSION_MATCH "${LIB_VERSION}" )
set( ${PROJECT_NAME}_MAJOR_VERSION "${CMAKE_MATCH_1}" )

string( REGEX MATCH "define[ \t]+LIBRARY_MINOR_VERSION[ \t]+([0-9]+)+"
        LIBRARY_MINOR_VERSION_MATCH "${LIB_VERSION}" )
set( ${PROJECT_NAME}_MINOR_VERSION "${CMAKE_MATCH_1}" )

string( REGEX MATCH "define[ \t]+LIBRARY_PATCH_VERSION[ \t]+([0-9]+)+"
        LIBRARY_PATCH_VERSION_MATCH "${LIB_VERSION}" )
set( ${PROJECT_NAME}_PATCH_VERSION "${CMAKE_MATCH_1}" )

set( ${PROJECT_NAME}_VERSION
        ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION} )

#---------------------------------------------------------------------------------------------------
#
#   Target properties
#
set_target_properties( lib${PROJECT_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_VERSION}
        CLEAN_DIRECT_OUTPUT 1
        OUTPUT_NAME ${PROJECT_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME} )
