cmake_minimum_required( VERSION 3.0 )

project( visualizor_2d )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++17 -O3 -Wall -lpthread" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_STANDARD 20 )

# Add image visualizor.
if( NOT TARGET lib_2d_visualizor )
    add_subdirectory( src ${PROJECT_SOURCE_DIR}/build/lib_2d_visualizor )
endif()

# Create executable target to test visualizor.
add_executable( test_visualizor
    test/test_visualizor.cpp
)
target_link_libraries( test_visualizor
    lib_2d_visualizor
)

# Create executable target to test loda and save image.
add_executable( test_load_and_save
    test/test_load_and_save.cpp
)
target_link_libraries( test_load_and_save
    lib_2d_visualizor
)
