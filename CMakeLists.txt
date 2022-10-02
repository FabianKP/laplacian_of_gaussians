cmake_minimum_required(VERSION 3.22)
project(blobDetection VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(examples)
add_subdirectory(tests)

# Setup library as header-only
include(GNUInstallDirs)
add_library(blobDetection INTERFACE)
target_include_directories(
        ${PROJECT_NAME}
        INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(blobDetection INTERFACE cxx_std_17)


