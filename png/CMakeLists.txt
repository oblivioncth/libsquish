# Add via ob standard executable
include(OB/Executable)
ob_add_standard_executable(${PNG_TARGET_NAME}
    NAMESPACE "${PROJECT_NAMESPACE}"
    ALIAS "${PNG_ALIAS_NAME}"
    SOURCE
        squishpng.cpp
    LINKS
        PRIVATE
            Squish::Squish
            PNG::PNG
    CONFIG STANDARD
)
