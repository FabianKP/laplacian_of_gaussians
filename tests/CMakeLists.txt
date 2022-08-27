

find_package(Boost REQUIRED COMPONENTS system iostreams)
include_directories(${Boost_INCLUDE_DIRS})
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(test_gaussian_filter_run testGaussianFilter.cpp)
target_link_libraries(test_gaussian_filter_run ${Boost_LIBRARIES})
target_link_libraries(test_gaussian_filter_run ${OpenCV_LIBS})

add_executable(test_gaussian_blob_run testGaussianBlob.cpp)
target_link_libraries(test_gaussian_blob_run ${OpenCV_LIBS})

add_executable(test_scale_space_representation testScaleSpaceRepresentation.cpp)
target_link_libraries(test_scale_space_representation ${OpenCV_LIBS})

add_executable(test_log testlog.cpp)
target_link_libraries(test_log ${OpenCV_LIBS})

add_executable(test_dilate3d testDilate3D.cpp)
target_link_libraries(test_dilate3d ${OpenCV_LIBS})

add_executable(test_local_min_max testLocalMinMax.cpp)
target_link_libraries(test_local_min_max ${OpenCV_LIBS})

add_executable(test_strict_local_max3d testStrictLocalMaximizer3D.cpp)
target_link_libraries(test_strict_local_max3d ${OpenCV_LIBS})

add_executable(test_check_overlap testCheckOverlap.cpp)
target_link_libraries(test_check_overlap ${OpenCV_LIBS})

add_executable(test_paint_blobs testPaintBlobs.cpp)
target_link_libraries(test_paint_blobs ${OpenCV_LIBS})

# Copy test image to current output directoy.
file(COPY "test_image.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})