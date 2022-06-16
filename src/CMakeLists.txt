include (${CMAKE_CURRENT_LIST_DIR}/Files/CMakeLists.txt) # file cmake file
include (${CMAKE_CURRENT_LIST_DIR}/OpenGLWidget/CMakeLists.txt) # openglwidget cmake file

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Qt5 COMPONENTS Widgets  REQUIRED)

#set(EXECUTABLE_OUTPUT_PATH path)

set(CMAKE_AUTOMOC ON) # auto create moc file
set(CMAKE_AUTORCC ON) # auto create rcc file
set(CMAKE_AUTOUIC ON) # auto create uic file

set(CMAKE_PREFIX_PATH D:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5/
E:/project/FEAStudio/deps/freetype-2.10.1/objs/)

find_package(Qt5 COMPONENTS Widgets REQUIRED) # find qt library

set(SOURCECODE ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MainWindow.h
    ${CMAKE_CURRENT_LIST_DIR}/MainWindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/appicon.rc
    ${CMAKE_CURRENT_LIST_DIR}/mainresource.qrc)

add_executable(${PROJECT_NAME} ${SOURCECODE})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets openglwidget stlfile) # add library