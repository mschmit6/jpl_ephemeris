cmake_minimum_required(VERSION 3.20)

project(jpl_ephemeris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -Wall -Wextra -Wno-psabi)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-ggdb3 -Wall -Wextra -Weffc++ -Wno-psabi)
endif()

# Include directories only affects targets in current CMAKE file
include_directories(
    ${CMAKE_INSTALL_PREFIX}/include ./
)

# Get all source files in the jpl_ephemeris directory
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS jpl_ephemeris/*.cpp)

# Create a shared library
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# Set the output directory for the shared library
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Get all header files in the jpl_ephemeris directory
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS jpl_ephemeris/*.hpp)

# Copy header files to the build/{preset}/include directory, maintaining folder structure
foreach(HEADER_FILE ${HEADER_FILES})
    get_filename_component(DIR ${HEADER_FILE} DIRECTORY)
    file(RELATIVE_PATH REL_DIR ${CMAKE_SOURCE_DIR}/jpl_ephemeris ${DIR})
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/jpl_ephemeris/${REL_DIR})
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HEADER_FILE} ${CMAKE_BINARY_DIR}/include/jpl_ephemeris/${REL_DIR}/)
endforeach()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/jpl_ephemeris/jpl_ephemeris.hpp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/)

# Enforce .so extension
if (APPLE)
    SET_TARGET_PROPERTIES(jpl_ephemeris PROPERTIES SUFFIX .so)
endif (APPLE)
