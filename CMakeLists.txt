# CMake build for libsquish
#
# Original library by Simon Brown (si@sjbrown.co.uk)
# Original CMake implementation by Stefan Roettger (snroettg@gmail.com)
# Current CMake implementation by Christian Heimlich (chris@pcserenity.com)

#================= Project Setup ==========================

# CMake
cmake_minimum_required(VERSION 3.23.0...3.25.0)

# Project
# NOTE: DON'T USE TRAILING ZEROS IN VERSIONS
project(Squish
    VERSION 1.15
    LANGUAGES CXX
    DESCRIPTION "(De)compression of images that conforms to the S3TC/DXT standard"
)

# Get helper scripts
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FetchOBCMake.cmake)
fetch_ob_cmake("aa228b4724de8380ebf4f1db15491b37ad598fb7")

# Initialize project according to standard rules
include(OB/Project)
ob_standard_project_setup()

# Additional project variables
set(PROJECT_FORMAL_NAME "libsquish")

# Configuration options
option(SQUISH_USE_OPENMP "Build with OpenMP." ON)
option(SQUISH_USE_SSE2 "Build with SSE2." ON)
option(SQUISH_USE_ALTIVEC "Build with Altivec." OFF)
option(SQUISH_EXTRAS "Build extra tools." OFF)
option(SQUISH_DOCS "Build the squish documentation." OFF)
option(BUILD_SHARED_LIBS "Build shared libraries." OFF) # Redundant due to OB, but explicit

# C++
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#================= Build =========================

# Import OpenMP
if(SQUISH_USE_OPENMP)
    find_package(OpenMP COMPONENTS C CXX)
endif()

# Process Targets
set(LIB_TARGET_NAME ${PROJECT_NAMESPACE_LC}_${PROJECT_NAMESPACE_LC})
set(LIB_ALIAS_NAME ${PROJECT_NAMESPACE})
set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${LIB_PATH}")

if(SQUISH_EXTRAS)
    set(GEN_TARGET_NAME ${PROJECT_NAMESPACE_LC}_gen)
    set(GEN_ALIAS_NAME Generator)
    add_subdirectory(gen)

    find_package(PNG)
    if(PNG_FOUND)
        set(PNG_TARGET_NAME ${PROJECT_NAMESPACE_LC}_png)
        set(PNG_ALIAS_NAME Png)
        add_subdirectory(png)
    endif()
endif()

if(SQUISH_DOCS)
    set(DOC_TARGET_NAME ${PROJECT_NAMESPACE_LC}_docs)
    add_subdirectory(doc)
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
