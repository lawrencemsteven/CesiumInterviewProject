#include <TerrainHeightmap.h>

int main() {
	std::filesystem::path preEruptionLocation{MOUNT_ST_HELENS_DATA_FOLDER};
	preEruptionLocation.append("pre.data");

	std::filesystem::path postEruptionLocation{MOUNT_ST_HELENS_DATA_FOLDER};
	postEruptionLocation.append("post.data");

	TerrainHeightmap::Terrain preEruptionTerrain{preEruptionLocation, {512, 512}};
	TerrainHeightmap::Terrain postEruptionTerrain{postEruptionLocation, {512, 512}};

	uint32_t x1{15};
	uint32_t y1{60};
	uint32_t x2{60};
	uint32_t y2{15};

	std::cout << "\nMount St. Helens Distance Calculator:" << std::endl;
	std::cout << "X1: ";
	std::cin >> x1;
	std::cout << "Y1: ";
	std::cin >> y1;
	std::cout << "X2: ";
	std::cin >> x2;
	std::cout << "Y2: ";
	std::cin >> y2;

	const auto preEruptionDistance	= preEruptionTerrain.walk({x1, y1}, {x2, y2});
	const auto postEruptionDistance = postEruptionTerrain.walk({x1, y1}, {x2, y2});
	std::cout << "\nDistance Pre-Eruption:  " << preEruptionDistance << "m" << std::endl;
	std::cout << "Distance Post-Eruption: " << postEruptionDistance << "m" << std::endl;
	std::cout << "Difference in Distance: " << postEruptionDistance - preEruptionDistance << "m\n"
			  << std::endl;
}