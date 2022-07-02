set(CMAKE_PREFIX_PATH D:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5/)


include (${CMAKE_CURRENT_LIST_DIR}/fileanalysis/CMakeLists.txt) # file cmake file
include (${CMAKE_CURRENT_LIST_DIR}/OpenGLWidget/CMakeLists.txt) # openglwidget cmake file
include (${CMAKE_CURRENT_LIST_DIR}/geometry/CMakeLists.txt) # openglwidget cmake file
include (${CMAKE_CURRENT_LIST_DIR}/msghandle/CMakeLists.txt) # openglwidget cmake file
include (${CMAKE_CURRENT_LIST_DIR}/standarttools/CMakeLists.txt) # openglwidget cmake file

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Qt5 COMPONENTS Widgets  REQUIRED)

#set(EXECUTABLE_OUTPUT_PATH path)

set(CMAKE_AUTOMOC ON) # auto create moc file
set(CMAKE_AUTORCC ON) # auto create rcc file
set(CMAKE_AUTOUIC ON) # auto create uic file


find_package(Qt5 COMPONENTS Widgets Concurrent REQUIRED) # find qt library

file(GLOB_RECURSE SOURCECODE ${CMAKE_CURRENT_LIST_DIR}/*.h
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.rc
    ${CMAKE_CURRENT_LIST_DIR}/*.qrc)

add_executable(${PROJECT_NAME} ${SOURCECODE})

target_link_libraries(${PROJECT_NAME} PRIVATE 
Qt5::Widgets 
Qt5::Concurrent
openglwidget 
fileanalysis
geometry
msghandle
standarttools
) # add library