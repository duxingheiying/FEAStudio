include_directories(openglwidget PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL REQUIRED) # find qt library

set(CMAKE_DEBUG_POSTFIX "d")
#set(CMAKE_RELEASE_POSTFIX "_r") 
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/OpenGLWidget/)

file(GLOB_RECURSE OPENGLWIDGET_SRC 
${CMAKE_CURRENT_LIST_DIR}/*.h 
${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(openglwidget STATIC ${OPENGLWIDGET_SRC})

target_include_directories(openglwidget PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(openglwidget PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL stlfile) # add library