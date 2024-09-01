# CMake build for libsquish
#
# Original library by Simon Brown (si@sjbrown.co.uk)
# Original CMake implementation by Stefan Roettger (snroettg@gmail.com)
# Current CMake implementation by Christian Heimlich (chris@pcserenity.com)

#================= Project Setup ==========================

# CMake
cmake_minimum_required(VERSION 3.23.0...3.26.0)

# Project
# NOTE: DON'T USE TRAILING ZEROS IN VERSIONS
project(Squish
    VERSION 1.15.1.1
    LANGUAGES CXX
    DESCRIPTION "S3TC/DXT compliant image compression"
)

# Get helper scripts
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FetchOBCMake.cmake)
fetch_ob_cmake("v0.3.5")

# Initialize project according to standard rules
include(OB/Project)
ob_standard_project_setup(
    NAMESPACE "libsquish"
)

# Configuration options
option(LIBSQUISH_USE_OPENMP "Build with OpenMP." ON)
option(LIBSQUISH_USE_SSE2 "Build with SSE2." ON)
option(LIBSQUISH_USE_ALTIVEC "Build with Altivec." OFF)
option(LIBSQUISH_EXTRAS "Build extra tools." OFF)
option(LIBSQUISH_DOCS "Build the squish documentation." OFF)
option(LIBSQUISH_TESTS "Build the squish tests." OFF)
option(BUILD_SHARED_LIBS "Build shared libraries." OFF) # Redundant due to OB, but explicit

# C++
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#================= Build =========================

# Import OpenMP
if(LIBSQUISH_USE_OPENMP)
    find_package(OpenMP COMPONENTS CXX)
endif()

# Target - Lib
set(LIB_TARGET_NAME ${PROJECT_NAMESPACE_LC}_${PROJECT_NAME_LC})
set(LIB_ALIAS_NAME ${PROJECT_NAME})
set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${LIB_PATH}")

# Targets - Extras (Generator, Png)
set(GEN_TARGET_NAME ${PROJECT_NAMESPACE_LC}_gen)
set(GEN_ALIAS_NAME Generator)
set(PNG_TARGET_NAME ${PROJECT_NAMESPACE_LC}_png)
set(PNG_ALIAS_NAME Png)
if(LIBSQUISH_EXTRAS)
    add_subdirectory(gen)

    find_package(PNG)
    if(PNG_FOUND)
        add_subdirectory(png)
    endif()
endif()

# Target - Doc
if(LIBSQUISH_DOCS)
    set(DOC_TARGET_NAME ${PROJECT_NAMESPACE_LC}_docs)
    add_subdirectory(doc)
endif()

# Targets - Tests
if(LIBSQUISH_TESTS)
    enable_testing()
    set(TESTS_TARGET_PREFIX ${PROJECT_NAMESPACE_LC})
    set(TESTS_COMMON_TARGET "${TESTS_TARGET_PREFIX}_tst_common")
    add_subdirectory(tests)
endif()

#--------------------Package Config-----------------------

ob_standard_project_package_config(
    COMPATIBILITY "SameMajorVersion"
    CONFIG STANDARD
        TARGET_CONFIGS
            TARGET "${PROJECT_NAMESPACE}::${LIB_ALIAS_NAME}" COMPONENT "${LIB_ALIAS_NAME}" DEFAULT
            TARGET "${PROJECT_NAMESPACE}::${GEN_ALIAS_NAME}" COMPONENT "${GEN_ALIAS_NAME}" OPTIONAL
            TARGET "${PROJECT_NAMESPACE}::${PNG_ALIAS_NAME}" COMPONENT "${PNG_ALIAS_NAME}" OPTIONAL
)

#================= Install ==========================

ob_standard_project_misc_install()

#====================== CPack ==============================

include(OB/Packaging)
ob_standard_project_package(VENDOR "oblivioncth")
