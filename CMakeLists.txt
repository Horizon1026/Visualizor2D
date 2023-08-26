cmake_minimum_required( VERSION 3.10 )

project( visualizor_2d )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++17 -O3 -Wall -lpthread" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_STANDARD 17 )

# Add visualizor.
if ( NOT TARGET lib_slam_visualize )
    add_subdirectory( src ${PROJECT_SOURCE_DIR}/build/lib_slam_visualize )
endif()

# Create executable target to test visualizor.
add_executable( test_visualizor
    test/test_visualizor.cpp
)
target_link_libraries( test_visualizor
    lib_slam_visualize
)
