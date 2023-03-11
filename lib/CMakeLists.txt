# Handle optional features
include(OB/Utility)
ob_get_system_bitness(system_bitness)

set(squish_links "")
set(squish_defs "")
set(squish_opts "")

if(SQUISH_USE_OPENMP AND OpenMP_FOUND)
    list(APPEND squish_links "OpenMP::OpenMP_C OpenMP::OpenMP_CXX")
    list(APPEND squish_defs "SQUISH_USE_OPENMP")
endif()

if(SQUISH_USE_SSE2 AND CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    list(APPEND squish_defs "SQUISH_USE_SSE=2")

    if(MSVC AND system_bitness EQUAL 32)
        list(APPEND squish_opts "/arch:SSE2")
    elseif(NOT MSVC)
        list(APPEND squish_opts "-msse2")
    endif()
endif()

if(SQUISH_USE_ALTIVEC AND CMAKE_SYSTEM_PROCESSOR STREQUAL "powerpc")
    list(APPEND squish_defs "SQUISH_USE_ALTIVEC=1")
    list(APPEND squish_opts "-maltivec")
endif()

# Add via ob standard library
include(OB/Library)
ob_add_standard_library(${LIB_TARGET_NAME}
    NAMESPACE "${PROJECT_NAMESPACE}"
    ALIAS "${LIB_ALIAS_NAME}"
    EXPORT_HEADER
        BASE_NAME "${PROJECT_NAMESPACE_UC}"
        PATH "${PROJECT_NAMESPACE_LC}/${PROJECT_NAMESPACE_LC}_export.h"
    HEADERS_PRIVATE
        alpha.h
        clusterfit.h
        colourblock.h
        colourfit.h
        colourset.h
        maths.h
        rangefit.h
        simd.h
        simd_float.h
        simd_sse.h
        simd_ve.h
        singlecolourfit.h
        singlecolourlookup.inl
    HEADERS_API
        COMMON "${PROJECT_NAMESPACE_LC}"
        FILES
            squish.h
    IMPLEMENTATION
        alpha.cpp
        clusterfit.cpp
        colourblock.cpp
        colourfit.cpp
        colourset.cpp
        maths.cpp
        rangefit.cpp
        singlecolourfit.cpp
        squish.cpp
    LINKS
        PRIVATE ${squish_links}
    DEFINITIONS
        PRIVATE ${squish_defs}
    OPTIONS
        PRIVATE ${squish_opts}
    CONFIG STANDARD
)

# Extra target modifications
set_target_properties(${LIB_TARGET_NAME} PROPERTIES
    OSX_ARCHITECTURES "i386;ppc"
)

