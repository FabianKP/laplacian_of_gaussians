cmake_minimum_required(VERSION 3.22)
project(blobs_cpp)

set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(examples)
add_subdirectory(tests)