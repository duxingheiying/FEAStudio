include (${CMAKE_CURRENT_LIST_DIR}/File/CMakeLists.txt)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

set(SOURCECODE ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MainWindow.h
    ${CMAKE_CURRENT_LIST_DIR}/MainWindow.cpp)

add_executable(${PROJECT_NAME} ${SOURCECODE})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets) # Qt dynamic library