

find_package(Boost REQUIRED COMPONENTS system iostreams)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(test_gaussian_filter_run testGaussianFilter.cpp)
target_link_libraries(test_gaussian_filter_run ${Boost_LIBRARIES})