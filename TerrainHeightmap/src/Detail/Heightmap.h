#pragma once

namespace TerrainHeightmap::Detail {

	class Heightmap {
	public:
		Heightmap(const std::filesystem::path& dataPath, const glm::ivec2& resolution);

		int8_t getHeight(const glm::ivec2& pos) const;

		const glm::ivec2& getResolution() const;

	private:
		std::vector<int8_t> m_heights;
		glm::ivec2 m_resolution;

		std::size_t convert2Dto1D(const glm::ivec2& val);
		void readHeightmapData(const std::filesystem::path& dataPath);
	};

}