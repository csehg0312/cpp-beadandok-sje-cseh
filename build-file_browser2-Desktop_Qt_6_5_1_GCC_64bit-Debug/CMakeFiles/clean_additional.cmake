# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/file_browser2_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/file_browser2_autogen.dir/ParseCache.txt"
  "file_browser2_autogen"
  )
endif()
