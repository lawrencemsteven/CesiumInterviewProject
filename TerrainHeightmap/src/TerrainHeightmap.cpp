#include "TerrainHeightmap.h"

namespace TerrainHeightmap {

	Terrain::Terrain(const std::filesystem::path& dataPath, const glm::uvec2& resolution)
		: m_heightmap{dataPath, resolution} {}

	double Terrain::walk(const glm::uvec2& start, const glm::uvec2& end) const {
		double horizontalDistTraveled = 0.0;
		double verticalDistTraveled	  = 0.0;

		enum IntersectionType { None, Horizonal, Vertical, Diagonal } intersectionType;

		int8_t verticalModifier	  = end.y > start.y;
		int8_t horizontalModifier = end.x > start.x;

		glm::vec2 origin	= start;
		glm::vec2 direction = glm::normalize(glm::vec2(end) - glm::vec2(start));

		glm::uvec2 containingBox{start};
		if (verticalModifier == 0) {
			containingBox.y -= 1;
		}
		if (horizontalModifier == 0) {
			containingBox.x -= 1;
		}

		glm::vec2 intersectionPoint{};

		while (horizontalDistTraveled <=
			   abs(static_cast<double>(end.x) - static_cast<double>(start.x))) {
			std::optional<glm::vec2> intersectionOpt{};
			intersectionType = None;
			float minDist	 = 1.5f;

			// Diagonal Line
			intersectionOpt = lineToLineIntersection(
				origin, direction, {glm::vec2{containingBox} + glm::vec2{0.5f, 0.5f}},
				glm::normalize(glm::vec2{1.0f, -1.0f}));
			if (intersectionOpt.has_value() && intersectionOpt.value() != origin) {
				intersectionPoint = intersectionOpt.value();
				minDist			  = glm::distance(origin, intersectionPoint);
				intersectionType  = Diagonal;
			}

			// Vertical Line
			intersectionOpt = lineToLineIntersection(
				origin, direction, {containingBox.x + horizontalModifier, 0}, {0, 1});
			if (intersectionOpt.has_value()) {
				const float newDist = glm::distance(origin, intersectionOpt.value());
				if (minDist > newDist) {
					minDist			  = newDist;
					intersectionPoint = intersectionOpt.value();
					intersectionType  = Vertical;
				}
			}

			// Horizontal Line
			intersectionOpt = lineToLineIntersection(
				origin, direction, {0, containingBox.y + verticalModifier}, {1, 0});
			if (intersectionOpt.has_value()) {
				const float newDist = glm::distance(glm::vec2{origin}, intersectionOpt.value());
				if (minDist > newDist) {
					minDist			  = newDist;
					intersectionPoint = intersectionOpt.value();
					intersectionType  = Horizonal;
				}
			}

			// Walk point
			switch (intersectionType) {
				case Diagonal:
					horizontalDistTraveled += minDist;
					verticalDistTraveled += glm::abs(m_heightmap.getHeight(intersectionPoint) -
													 m_heightmap.getHeight(origin));
					origin = intersectionPoint;
					break;
				case Vertical:
					horizontalDistTraveled += minDist;
					verticalDistTraveled += glm::abs(m_heightmap.getHeight(intersectionPoint) -
													 m_heightmap.getHeight(origin));
					origin = intersectionPoint;
					containingBox.x += horizontalModifier == 1 ? 1 : -1;
					break;
				case Horizonal:
					horizontalDistTraveled += minDist;
					verticalDistTraveled += glm::abs(m_heightmap.getHeight(intersectionPoint) -
													 m_heightmap.getHeight(origin));
					origin = intersectionPoint;
					containingBox.y += verticalModifier == 1 ? 1 : -1;
					break;
			}
		}

		return verticalDistTraveled * 11 + horizontalDistTraveled * 30;
	}

	double Terrain::getHeight(const glm::vec2& pos) const {
		return m_heightmap.getHeight(pos);
	}

	uint8_t Terrain::getHeight(const glm::uvec2& pos) const {
		return m_heightmap.getHeight(pos);
	}

	std::optional<glm::vec2> Terrain::lineToLineIntersection(const glm::vec2& point1,
															 const glm::vec2& dir1,
															 const glm::vec2& point2,
															 const glm::vec2& dir2) const {
		const glm::vec2 dirDiff = min(dir1 - dir2, dir2 - dir1);
		if (glm::length(dirDiff) <= 0.001) {
			// Lines are parallel
			return std::nullopt;
		}

		const float t = ((point2.x - point1.x) * dir2.y - (point2.y - point1.y) * dir2.x) /
						(dir1.x * dir2.y - dir1.y * dir2.x);

		return point1 + t * dir1;
	}

}