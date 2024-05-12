#include "TerrainHeightmap.h"

namespace TerrainHeightmap {

	Terrain::Terrain(const std::filesystem::path& dataPath, const glm::ivec2& resolution)
		: m_heightmap{dataPath, resolution} {}

	double Terrain::walk(const glm::vec2& start, const glm::vec2& end) const {
		// TODO: Use heightmap walk to determine distance
		return 0.0;
	}

	double Terrain::walk(const glm::ivec2& start, const glm::ivec2& end) const {
		return walk(glm::vec2{start}, glm::vec2{end});
	}

}