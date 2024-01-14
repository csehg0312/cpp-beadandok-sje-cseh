# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/tamagochi-pnged_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/tamagochi-pnged_autogen.dir/ParseCache.txt"
  "tamagochi-pnged_autogen"
  )
endif()
