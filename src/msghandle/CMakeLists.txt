include_directories(msghandle PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED) # find qt library

set(CMAKE_DEBUG_POSTFIX "d")
#set(CMAKE_RELEASE_POSTFIX "_r") 
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/msghandle/)

file(GLOB_RECURSE MESSAGEHANDLE_SRC 
${CMAKE_CURRENT_LIST_DIR}/*.h 
${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(msghandle STATIC ${MESSAGEHANDLE_SRC})

target_include_directories(msghandle PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(msghandle PRIVATE 
Qt5::Core 
Qt5::Gui 
Qt5::Widgets) # add library
