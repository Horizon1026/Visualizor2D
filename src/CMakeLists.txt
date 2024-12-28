aux_source_directory( . AUX_SRC_2D_VISUALIZOR )

# Add some components of slam utility.
set( SLAM_UTILITY_PATH ${PROJECT_SOURCE_DIR}/../Slam_Utility )
if ( NOT TARGET lib_slam_utility_basic_type )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/basic_type ${PROJECT_SOURCE_DIR}/build/lib_slam_utility_basic_type )
endif()
if ( NOT TARGET lib_slam_utility_log )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/log ${PROJECT_SOURCE_DIR}/build/lib_slam_utility_log )
endif()
if ( NOT TARGET lib_slam_utility_memory )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/memory ${PROJECT_SOURCE_DIR}/build/lib_slam_utility_memory )
endif()
if ( NOT TARGET lib_slam_utility_operate )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/operate ${PROJECT_SOURCE_DIR}/build/lib_slam_utility_operate )
endif()

# Add all relative components of slam utility data type.
if ( NOT TARGET lib_image )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/data_type/image ${PROJECT_SOURCE_DIR}/build/lib_image )
endif()

# Add image painter.
set( IMAGE_PAINTER_PATH ${PROJECT_SOURCE_DIR}/../Image_Painter )
if ( NOT TARGET lib_image_painter )
    add_subdirectory( ${IMAGE_PAINTER_PATH}/src ${PROJECT_SOURCE_DIR}/build/lib_image_painter )
endif()

# Add dependence for visualizor.
if ( NOT TARGET lib_visualize_base_glad_khr )
    add_subdirectory( glad+khr ${PROJECT_SOURCE_DIR}/build/lib_visualize_base_glad_khr )
endif()
if ( NOT TARGET lib_visualize_base_stb )
    add_subdirectory( stb_image ${PROJECT_SOURCE_DIR}/build/lib_visualize_base_stb )
endif()

# Create library.
add_library( lib_2d_visualizor ${AUX_SRC_2D_VISUALIZOR} )
target_include_directories( lib_2d_visualizor PUBLIC
    .
    glad+khr
    stb_image
)
target_link_libraries( lib_2d_visualizor
    lib_slam_utility_basic_type
    lib_slam_utility_log
    lib_slam_utility_memory
    lib_slam_utility_operate

    lib_image
    lib_image_painter

    lib_visualize_base_glad_khr
    lib_visualize_base_stb
)

# Check compile environment. If environment is windows, add additional dependence.
if ( "${COMPILE_ENV}" STREQUAL "windows" )
    # If environment is windows, add special dependence.
    target_include_directories( lib_2d_visualizor PUBLIC
        "E:/glfw-3.3.8.bin.WIN64/include"
    )
    target_link_libraries( lib_2d_visualizor
        "E:/glfw-3.3.8.bin.WIN64/lib-mingw-w64/glfw3.dll"
    )
else()
    # If environment is linux, add special dependence.
    target_link_libraries( lib_2d_visualizor
        -lglfw
    )
endif()
