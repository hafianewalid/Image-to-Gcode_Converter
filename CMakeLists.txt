cmake_minimum_required(VERSION 3.1)
project(slice)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 14)

add_executable(slice main.cpp img2forme.cpp img2forme.h Freeman.h Freeman.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
