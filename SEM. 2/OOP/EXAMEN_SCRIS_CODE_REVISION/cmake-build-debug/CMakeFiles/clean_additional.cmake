# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/EXAMEN_SCRIS_CODE_REVISION_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/EXAMEN_SCRIS_CODE_REVISION_autogen.dir/ParseCache.txt"
  "EXAMEN_SCRIS_CODE_REVISION_autogen"
  )
endif()
