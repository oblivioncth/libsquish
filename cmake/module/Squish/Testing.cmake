# Adds a test
macro(libsquish_add_test name)
    add_executable(${name})
    add_test(NAME ${name} COMMAND ${name})
    target_sources(${name} PRIVATE ${ARGN})
    target_link_libraries(${name}
        PRIVATE
            ${TESTS_COMMON_ALIAS_TARGET}
            libsquish::Squish
    )
endmacro()
