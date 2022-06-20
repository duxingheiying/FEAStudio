cmake_minimum_required(VERSION 3.19.0)

project(FEAStudio VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

include(${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)

link_directories(${CMAKE_CURRENT_LIST_DIR}/deps/freetype-2.10.1/objs/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#install(DIRECTORY fonts/ DESTINATION fonts)

# set control enbale or disable
if(WIN32)
set_target_properties( ${PROJECT_NAME}
    PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"  # show window without console in win32
#               LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE" # show window with console in win32
               LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
               LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
               LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
)
endif(WIN32)
