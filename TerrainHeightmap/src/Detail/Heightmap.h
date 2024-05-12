#pragma once

namespace TerrainHeightmap::Detail {

	class Heightmap {
	public:
		Heightmap(const std::filesystem::path& dataPath, const glm::uvec2& resolution);

		uint8_t getHeight(const glm::uvec2& pos) const;

		const glm::uvec2& getResolution() const;

	private:
		std::vector<uint8_t> m_heights;
		glm::uvec2 m_resolution;

		std::size_t convert2Dto1D(const glm::uvec2& val) const;
		void readHeightmapData(const std::filesystem::path& dataPath);
	};

}