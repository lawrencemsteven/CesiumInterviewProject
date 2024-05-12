#include "Heightmap.h"

namespace TerrainHeightmap::Detail {

	Heightmap::Heightmap(const std::filesystem::path& dataPath, const glm::ivec2& resolution)
		: m_resolution{resolution} {
		m_heights.resize(m_resolution.x * m_resolution.y);
		readHeightmapData(dataPath);
	}

	int8_t Heightmap::getHeight(const glm::ivec2& pos) const {
		// TODO: Return height at position
		return 0;
	}

	const glm::ivec2& Heightmap::getResolution() const {
		return m_resolution;
	}

	std::size_t Heightmap::convert2Dto1D(const glm::ivec2& val) {
		return val.y * m_resolution.x + val.x;
	}

	void Heightmap::readHeightmapData(const std::filesystem::path& dataPath) {
		// TODO: Read in heightmap data
	}
}