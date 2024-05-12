#include "Heightmap.h"

namespace TerrainHeightmap::Detail {

	Heightmap::Heightmap(const std::filesystem::path& dataPath, const glm::uvec2& resolution)
		: m_resolution{resolution} {
		m_heights.resize(m_resolution.x * m_resolution.y);
		readHeightmapData(dataPath);
	}

	uint8_t Heightmap::getHeight(const glm::uvec2& pos) const {
		return m_heights[convert2Dto1D(pos)];
	}

	const glm::uvec2& Heightmap::getResolution() const {
		return m_resolution;
	}

	std::size_t Heightmap::convert2Dto1D(const glm::uvec2& val) const {
		return val.y * m_resolution.x + val.x;
	}

	void Heightmap::readHeightmapData(const std::filesystem::path& dataPath) {
		// Reset all heights
		std::fill(m_heights.begin(), m_heights.end(), 0u);

		// Open File
		std::ifstream fileStream{dataPath};
		if (!fileStream.is_open()) {
			std::cout << "ERROR: Failed to read file: " << dataPath << std::endl;
		}

		// Read all height data into m_heights
		char height;
		std::size_t idx{0};
		while (fileStream.get(height)) {
			m_heights[idx] = static_cast<uint8_t>(height);
			idx++;
		}

		fileStream.close();
	}
}