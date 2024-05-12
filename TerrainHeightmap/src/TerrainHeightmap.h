#pragma once

#include "Detail/Heightmap.h"

namespace TerrainHeightmap {

	class Terrain {
	public:
		Terrain(const std::filesystem::path& dataPath, const glm::ivec2& resolution);

		double walk(const glm::vec2& start, const glm::vec2& end) const;
		double walk(const glm::ivec2& start, const glm::ivec2& end) const;

	private:
		Detail::Heightmap m_heightmap;
	};

};