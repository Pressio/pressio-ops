
# versioning
#=====================================================================
# adapted from Eigen
file(READ "${CMAKE_SOURCE_DIR}/include/pressio/ops_macros.hpp" _pressio_ops_macros)

string(REGEX MATCH "define[ \t]+PRESSIO_OPS_MAJOR_VERSION[ \t]+([0-9]+)" _pressio_major_version_match "${_pressio_ops_macros}")
set(PRESSIO_OPS_MAJOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+PRESSIO_OPS_MINOR_VERSION[ \t]+([0-9]+)" _pressio_minor_version_match "${_pressio_ops_macros}")
set(PRESSIO_OPS_MINOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+PRESSIO_OPS_PATCH_VERSION[ \t]+([0-9]+)" _pressio_patch_version_match "${_pressio_ops_macros}")
set(PRESSIO_OPS_PATCH_VERSION "${CMAKE_MATCH_1}")
set(PRESSIO_OPS_VERSION_NUMBER ${PRESSIO_OPS_MAJOR_VERSION}.${PRESSIO_OPS_MINOR_VERSION}.${PRESSIO_OPS_PATCH_VERSION})
message("${Magenta}>> PRESSIO-OPS: version = ${PRESSIO_OPS_VERSION_NUMBER} ${ColourReset}")
