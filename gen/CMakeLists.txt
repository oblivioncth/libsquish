# Set custom output name
if(WIN32)
    set(gen_output_name "${PROJECT_NAME}${GEN_ALIAS_NAME}")
else()
    string(TOLOWER ${GEN_ALIAS_NAME} GEN_ALIAS_NAME_LC)
    set(gen_output_name "${PROJECT_NAME_LC}-${GEN_ALIAS_NAME_LC}")
endif()

# Add via ob standard executable
include(OB/Executable)
ob_add_standard_executable(${GEN_TARGET_NAME}
    NAMESPACE "${PROJECT_NAMESPACE}"
    ALIAS "${GEN_ALIAS_NAME}"
    OUTPUT_NAME "${gen_output_name}"
    SOURCE
        squishgen.cpp
    CONFIG STANDARD
)
