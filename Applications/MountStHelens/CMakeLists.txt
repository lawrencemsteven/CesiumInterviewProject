include(CMakeFiles.cmake)

add_executable(MountStHelens ${MountStHelens_Files})

target_link_libraries(MountStHelens TerrainHeightmap)

target_compile_definitions(MountStHelens PRIVATE MOUNT_ST_HELENS_DATA_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/data" )