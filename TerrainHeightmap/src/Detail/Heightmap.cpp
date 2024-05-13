#include "Heightmap.h"

namespace TerrainHeightmap::Detail {

	Heightmap::Heightmap(const std::filesystem::path& dataPath, const glm::uvec2& resolution)
		: m_resolution{resolution} {
		m_heights.resize(m_resolution.x * m_resolution.y);
		readHeightmapData(dataPath);
	}

	double Heightmap::getHeight(const glm::vec2& pos) const {
		const uint32_t lowY	 = static_cast<uint32_t>(std::floor(pos.y));
		const uint32_t highY = static_cast<uint32_t>(std::ceil(pos.y));
		const uint32_t lowX	 = static_cast<uint32_t>(std::floor(pos.x));
		const uint32_t highX = static_cast<uint32_t>(std::ceil(pos.x));

		glm::uvec2 vertA{};
		const glm::uvec2 vertB{highX, lowY};
		const glm::uvec2 vertC{lowX, highY};

		if (pos.x + pos.y >= 1.0f) {
			// Top Left
			vertA = {lowX, lowY};
		}
		else {
			// Bottom Right
			vertA = {highX, highY};
		}

		const auto weightsOpt = barycentricCoordinates(pos, vertA, vertB, vertC);
		if (!weightsOpt.has_value()) {
			std::cout << "ERROR: Divide by 0!" << std::endl;
			return 0.0;
		}
		const auto weights = weightsOpt.value();

		return getHeight(vertA) * weights[0] + getHeight(vertB) * weights[1] +
			   getHeight(vertC) * weights[2];
	}

	uint8_t Heightmap::getHeight(const glm::uvec2& pos) const {
		return m_heights[convert2Dto1D(pos)];
	}

	const glm::uvec2& Heightmap::getResolution() const {
		return m_resolution;
	}

	std::size_t Heightmap::convert2Dto1D(const glm::uvec2& val) const {
		// Clamp values in graph
		const std::size_t xValClamped = std::clamp(val.x, 0u, m_resolution.x);
		const std::size_t yValClamped = std::clamp(val.y, 0u, m_resolution.y);

		return yValClamped * static_cast<std::size_t>(m_resolution.x) + xValClamped;
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

	const std::optional<std::array<double, 3>>
	Heightmap::barycentricCoordinates(const glm::vec2& pos, const glm::vec2& a, const glm::vec2& b,
									  const glm::vec2& c) const {
		// Efficient Barycentric Coordinate Solver:
		// https://gamedev.stackexchange.com/a/23745

		std::array<double, 3> output;

		const glm::vec2 v0 = b - a;
		const glm::vec2 v1 = c - a;
		const glm::vec2 v2 = pos - a;
		const float d00	   = glm::dot(v0, v0);
		const float d01	   = glm::dot(v0, v1);
		const float d11	   = glm::dot(v1, v1);
		const float d20	   = glm::dot(v2, v0);
		const float d21	   = glm::dot(v2, v1);
		const float denom  = d00 * d11 - d01 * d01;

		if (denom == 0.0) {
			return std::nullopt;
		}

		output[0] = (d11 * d20 - d01 * d21) / denom;
		output[1] = (d00 * d21 - d01 * d20) / denom;
		output[2] = 1.0f - output[0] - output[1];

		return output;
	}

}