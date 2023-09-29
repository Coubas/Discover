# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles\\Discover_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Discover_autogen.dir\\ParseCache.txt"
  "Discover_autogen"
  )
endif()
