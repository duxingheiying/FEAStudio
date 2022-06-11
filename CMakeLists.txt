cmake_minimum_required(VERSION 3.19.0)

project(FEAStudio VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH D:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5/)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

set(SOURCECODE ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MainWindow.h
    ${CMAKE_CURRENT_LIST_DIR}/src/MainWindow.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)

add_executable(${PROJECT_NAME} ${SOURCECODE} "src/File/STLFile.h" "src/File/STLFile.cpp")

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

if(WIN32)
set_target_properties( ${PROJECT_NAME}
    PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"  # show window without console in win32
#               LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE" # show window with console in win32
               LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
               LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
               LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
)
endif(WIN32)
