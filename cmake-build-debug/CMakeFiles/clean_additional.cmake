# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/HRM_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/HRM_autogen.dir/ParseCache.txt"
  "HRM_autogen"
  )
endif()
