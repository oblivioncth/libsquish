#=== TESTS INTERFACE HELPER LIB ===

# Setup lib target
set(target_name "${TESTS_TARGET_PREFIX}_tst_common")
add_library(${target_name} INTERFACE)
add_library(${TESTS_COMMON_ALIAS_TARGET} ALIAS ${target_name})

target_sources(${target_name}
    PRIVATE
        include/libsquish_test_common.h
)

target_include_directories(${target_name}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)