include_directories(stlfile PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

set(CMAKE_DEBUG_POSTFIX "d")
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/File/)

file(GLOB_RECURSE STLFILE_SRC 
${CMAKE_CURRENT_LIST_DIR}/*.h 
${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(stlfile STATIC ${STLFILE_SRC})

target_include_directories(stlfile PRIVATE ${CMAKE_CURRENT_LIST_DIR})
