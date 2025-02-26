# adapted from Eigen
file(READ "${PROJECT_SOURCE_DIR}/include/pressio/ops_macros.hpp" _pressio_ops_macros)
string(REGEX MATCH "define[ \t]+PRESSIO_MAJOR_VERSION[ \t]+([0-9]+)" _major_version_match "${_pressio_ops_macros}")
set(PRESSIO_MAJOR_VERSION "${CMAKE_MATCH_1}")

string(REGEX MATCH "define[ \t]+PRESSIO_MINOR_VERSION[ \t]+([0-9]+)" _minor_version_match "${_pressio_ops_macros}")
set(PRESSIO_MINOR_VERSION "${CMAKE_MATCH_1}")

string(REGEX MATCH "define[ \t]+PRESSIO_PATCH_VERSION[ \t]+([0-9]+)" _patch_version_match "${_pressio_ops_macros}")
set(PRESSIO_PATCH_VERSION "${CMAKE_MATCH_1}")

set(PRESSIO_VERSION_NUMBER ${PRESSIO_MAJOR_VERSION}.${PRESSIO_MINOR_VERSION}.${PRESSIO_PATCH_VERSION})
message("${Magenta}>> PRESSIO-OPS: version = ${PRESSIO_VERSION_NUMBER} ${ColourReset}")
