#include "TerrainHeightmap.h"

namespace TerrainHeightmap {

	Terrain::Terrain(const std::filesystem::path& dataPath, const glm::uvec2& resolution)
		: m_heightmap{dataPath, resolution} {}

	double Terrain::walk(const glm::vec2& start, const glm::vec2& end) const {
		// TODO: Use heightmap walk to determine distance
		return 0.0;
	}

	double Terrain::walk(const glm::uvec2& start, const glm::uvec2& end) const {
		return walk(glm::vec2{start}, glm::vec2{end});
	}

	uint8_t Terrain::getHeight(const glm::vec2& pos) const {
		return m_heightmap.getHeight(pos);
	}

	uint8_t Terrain::getHeight(const glm::uvec2& pos) const {
		return m_heightmap.getHeight(pos);
	}
}