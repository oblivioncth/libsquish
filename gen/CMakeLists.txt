# Add via ob standard executable
include(OB/Executable)
ob_add_standard_executable(${GEN_TARGET_NAME}
    NAMESPACE "${PROJECT_NAMESPACE}"
    ALIAS "${GEN_ALIAS_NAME}"
    SOURCE
        squishgen.cpp
    CONFIG STANDARD
)
