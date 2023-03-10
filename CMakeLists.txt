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
fetch_ob_cmake("af237ed1688f7854943f58a61737f011e4df9ea4")

# Initialize project according to standard rules
include(OB/Project)
ob_standard_project_setup()


