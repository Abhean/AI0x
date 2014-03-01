cmake_minimum_required(VERSION 2.8)
project(ai0x)

FILE(GLOB_RECURSE Common_CPP "src/*.cpp")
#LIST(REMOVE_ITEM Common_CPP "${PROJECT_SOURCE_DIR}/build/*.cpp")

add_executable(ai0x src/main.cpp ${Common_CPP})

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src/3rd/rapidxml-1.13")
include_directories ("${PROJECT_SOURCE_DIR}/../../Software/boost_1_47_0")

LINK_DIRECTORIES(/usr/lib)
TARGET_LINK_LIBRARIES(ai0x GL GLEW glfw rt)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(GLFW REQUIRED)

add_subdirectory(src/Bitflow)



add_subdirectory(src/Foundation/Reflection)