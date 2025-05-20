aux_source_directory( . AUX_SRC_VISUALIZE_BASE_STB )

set( SLAM_UTILITY_PATH ${PROJECT_SOURCE_DIR}/../Slam_Utility )
if( NOT TARGET lib_slam_utility_basic_type )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/basic_type ${PROJECT_SOURCE_DIR}/build/lib_slam_utility_basic_type )
endif()

add_library( lib_visualize_base_stb ${AUX_SRC_VISUALIZE_BASE_STB} )
target_include_directories( lib_visualize_base_stb PUBLIC . )
target_link_libraries( lib_visualize_base_stb
    lib_slam_utility_basic_type
)
