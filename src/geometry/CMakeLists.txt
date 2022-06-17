include_directories(geometry PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED) # find qt library

set(CMAKE_DEBUG_POSTFIX "d")
#set(CMAKE_RELEASE_POSTFIX "_r") 
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/geometry/)

file(GLOB_RECURSE GEOMETRY_SRC 
${CMAKE_CURRENT_LIST_DIR}/*.h 
${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(geometry STATIC ${GEOMETRY_SRC})

target_include_directories(geometry PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(geometry PRIVATE 
Qt5::Core 
Qt5::Gui 
Qt5::Widgets) # add library
