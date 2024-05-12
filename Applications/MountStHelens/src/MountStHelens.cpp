#include <TerrainHeightmap.h>

int main() {
	std::filesystem::path preEruptionLocation{std::string{MOUNT_ST_HELENS_DATA_FOLDER} +
											  std::string{"/pre.data"}};
	// preEruptionLocation.append("pre.data");

	std::filesystem::path postEruptionLocation{MOUNT_ST_HELENS_DATA_FOLDER};
	postEruptionLocation.append("post.data");

	TerrainHeightmap::Terrain preEruptionTerrain{preEruptionLocation, {512, 512}};
	TerrainHeightmap::Terrain postEruptionTerrain{postEruptionLocation, {512, 512}};

	std::cout << "Pre Eruption Height:  "
			  << static_cast<uint32_t>(preEruptionTerrain.getHeight(glm::uvec2{50u, 50u}))
			  << std::endl;
	std::cout << "Post Eruption Height: "
			  << static_cast<uint32_t>(postEruptionTerrain.getHeight(glm::uvec2{50u, 50u}))
			  << std::endl;
}