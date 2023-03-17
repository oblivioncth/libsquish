# Include standard documentation target creator
include(OB/Documentation)

# Set project specific doxygen overrides
set(DOXYGEN_HTML_COLORSTYLE_HUE 232)
set(DOXYGEN_HTML_COLORSTYLE_SAT 75)
set(DOXYGEN_HTML_COLORSTYLE_GAMMA 75)

# Hide export statements from docs
list(APPEND DOXYGEN_PREDEFINED
    SQUISH_EXPORT=
)

# Setup documentation
ob_standard_documentation(${DOC_TARGET_NAME}
    DOXY_VER 1.9.4
    PROJ_NAME "${PROJECT_NAMESPACE}"
    INPUT_LIST
        "${LIB_PATH}/include"
)
