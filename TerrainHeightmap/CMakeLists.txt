include(CMakeFiles.cmake)

add_library(TerrainHeightmap STATIC ${TerrainHeightmap_Files})

target_include_directories(TerrainHeightmap
	PUBLIC
		"./src"
)

target_compile_features(TerrainHeightmap PUBLIC cxx_std_20)

target_precompile_headers(TerrainHeightmap PUBLIC "./src/Detail/TerrainHeightmapPCH.h")