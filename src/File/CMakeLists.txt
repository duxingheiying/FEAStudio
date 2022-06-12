include_directories(stlfile_library PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/File/)

file(GLOB_RECURSE STLFILE_SRC 
${CMAKE_CURRENT_LIST_DIR}/*.h 
${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(stlfile_library STATIC ${STLFILE_SRC})

target_include_directories(stlfile_library PRIVATE ${CMAKE_CURRENT_LIST_DIR})
