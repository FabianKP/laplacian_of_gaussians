
find_package(Boost REQUIRED COMPONENTS system iostreams)
include_directories(${Boost_INCLUDE_DIRS})
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(example1 example1.cpp)
target_link_libraries(example1 ${OpenCV_LIBS})
set(BLOBS "/home/fabian/pd/blobs_cpp/include")
target_include_directories(example1 PRIVATE ${BLOBS})

add_executable(example2 example2.cpp)
target_link_libraries(example2 ${OpenCV_LIBS})
target_include_directories(example2 PRIVATE ../include)


# Copy test image to current output directory.
file(COPY "almonds.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "hubble.jpg" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})