#pragma once

#include "Detail/Heightmap.h"

namespace TerrainHeightmap {

	class Terrain {
	public:
		Terrain(const std::filesystem::path& dataPath, const glm::uvec2& resolution);

		double walk(const glm::vec2& start, const glm::vec2& end) const;
		double walk(const glm::uvec2& start, const glm::uvec2& end) const;

		uint8_t getHeight(const glm::vec2& pos) const;
		uint8_t getHeight(const glm::uvec2& pos) const;

	private:
		Detail::Heightmap m_heightmap;
	};

};