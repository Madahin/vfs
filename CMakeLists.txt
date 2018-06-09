cmake_minimum_required(VERSION 3.0.2)
project(vfs CXX)

set(VERSION_MAJOR 0 CACHE STRING "Project major version number")
set(VERSION_MINOR 0 CACHE STRING "Project minor version number")
set(VERSION_PATCH 1 CACHE STRING "Project patch version number")
set(${PROJECT_NAME}_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

##########################################################
# Check the architecture                                 #
##########################################################

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(EX_PLATFORM 64)
    set(EX_PLATFORM_NAME "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(EX_PLATFORM 32)
    set(EX_PLATFORM_NAME "x32")
else()
    message(WARNING "Platform not supported")
endif()

if(DEFINED EX_PLATFORM)
    message("-- platform: ${EX_PLATFORM_NAME}")
endif()


##########################################################
# Compiler flags                                         #
##########################################################

# defines
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}" -DVERSION_MAJOR=${VERSION_MAJOR} -DVERSION_MINOR=${VERSION_MINOR} -DVERSION_PATCH=${VERSION_PATCH})

# C++ features
set(CMAKE_CXX_EXTENSIONS OFF)
# target_compile_features must be set after declaring targets

# Flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}") # default debug flags
    set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s -Os")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    else()
        # nothing special for gcc at the moment
    endif()
endif()



##########################################################
# Dependencies                                           #
##########################################################

# Doxygen
find_package(Doxygen 1.8.3)

# Google test
enable_testing()
find_package(GTest)


##########################################################
# Options                                                #
##########################################################

# Documentation
Option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT ${DOXYGEN_FOUND})
        message(FATAL_ERROR "Doxygen is needed to build the documentation")
    endif()

    set(doxy_main_page ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    # Little hack to add README.md to the indexed file in qtcreator
    configure_file(${doxy_main_page} ${doxy_main_page} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

# Test
Option(BUILD_TEST "Build tests" ${GTEST_FOUND})
if(BUILD_TEST)
    if(NOT ${GTEST_FOUND})
        message(FATAL_ERROR "Google Test is needed to build the test executable")
    endif()
endif()

##########################################################
# Include files and libraries                            #
##########################################################

#headers
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/test)

#files
FILE(
    GLOB_RECURSE
    files_lib
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/include/*.hpp
)

FILE(
    GLOB_RECURSE
    files_test
    ${PROJECT_SOURCE_DIR}/test/*.cpp
    ${PROJECT_SOURCE_DIR}/test/*.hpp
)

# Libraries
if(BUILD_TEST)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

##########################################################
# Build Targets                                          #
##########################################################

# vfs library
add_library(${PROJECT_NAME} SHARED ${files_lib})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# test
if(BUILD_TEST)
    add_executable(test_${PROJECT_NAME} ${files_test})
    target_compile_features(test_${PROJECT_NAME} PRIVATE cxx_std_17)
    target_link_libraries(test_${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})
endif()

