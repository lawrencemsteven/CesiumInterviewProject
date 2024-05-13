#pragma once

#include "Detail/Heightmap.h"

namespace TerrainHeightmap {

	class Terrain {
	public:
		Terrain(const std::filesystem::path& dataPath, const glm::uvec2& resolution);

		double walk(const glm::uvec2& start, const glm::uvec2& end) const;

		double getHeight(const glm::vec2& pos) const;
		uint8_t getHeight(const glm::uvec2& pos) const;

	private:
		Detail::Heightmap m_heightmap;

		std::optional<glm::vec2> lineToLineIntersection(const glm::vec2& point1,
														const glm::vec2& dir1,
														const glm::vec2& point2,
														const glm::vec2& dir2) const;
	};

};