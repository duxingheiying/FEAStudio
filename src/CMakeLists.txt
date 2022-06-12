include (${CMAKE_CURRENT_LIST_DIR}/File/CMakeLists.txt) # file cmake file
include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

#set(EXECUTABLE_OUTPUT_PATH path)

set(SOURCECODE ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MainWindow.h
    ${CMAKE_CURRENT_LIST_DIR}/MainWindow.cpp)

add_executable(${PROJECT_NAME} ${SOURCECODE})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets stlfile) # Qt dynamic library