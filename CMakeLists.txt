cmake_minimum_required(VERSION 2.8)
project(ai0x)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src/3rd/rapidxml-1.13")

FILE(GLOB_RECURSE Common_CPP "src/*.cpp")
add_executable(ai0x src/main.cpp ${Common_CPP})

LINK_DIRECTORIES(/usr/lib)

#external dependencies
find_package(Boost REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries (ai0x ${Boost_LIBRARY_DIRS})
endif (Boost_FOUND)

find_package(GLEW REQUIRED)
if (GLEW_FOUND) 
  include_directories(${GLEW_INCLUDE_PATH})
  target_link_libraries (ai0x ${GLEW_LIBRARY})
else (GLEW_FOUND)
  message(Error " GLEW not found")
endif (GLEW_FOUND)

find_package(GLFW REQUIRED)
if (GLFW_FOUND)
  include_directories(${GLFW_INCLUDE_DIRS})
  target_link_libraries (ai0x ${GLFW_LIBRARIES})
else (GLFW_FOUND)
  message(Error " GLFW not found")
endif (GLFW_FOUND)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries (ai0x ${OPENGL_LIBRARIES})
