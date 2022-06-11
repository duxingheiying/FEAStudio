# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FEAStudio_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FEAStudio_autogen.dir\\ParseCache.txt"
  "FEAStudio_autogen"
  )
endif()
