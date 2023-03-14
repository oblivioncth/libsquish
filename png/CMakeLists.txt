# Set custom output name
if(WIN32)
    set(png_output_name "${PROJECT_NAME}${PNG_ALIAS_NAME}")
else()
    string(TOLOWER ${PNG_ALIAS_NAME} PNG_ALIAS_NAME_LC)
    set(png_output_name "${PROJECT_NAME_LC}-${PNG_ALIAS_NAME_LC}")
endif()

# Add via ob standard executable
include(OB/Executable)
ob_add_standard_executable(${PNG_TARGET_NAME}
    NAMESPACE "${PROJECT_NAMESPACE}"
    ALIAS "${PNG_ALIAS_NAME}"
    OUTPUT_NAME "${png_output_name}"
    SOURCE
        squishpng.cpp
    LINKS
        PRIVATE
            libsquish::Squish
            PNG::PNG
    CONFIG STANDARD
)
