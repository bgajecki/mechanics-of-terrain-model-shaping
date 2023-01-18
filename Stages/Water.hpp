#pragma once

#include <Mesh.hpp>
#include <algorithm>
#include <numeric>
#include <array>

/**
* @brief Water plane which impact terrain mesh.
*/
class Water final : public engine::Mesh
{
	/**
	* @brief Type of to terrain vertices.
	*/
	using TerrainVertices = std::vector<engine::MeshVertex>;

public:
	/**
	* @brief Water constructor.
	* @param terrain Terrain mesh.
	*/
	Water(engine::Mesh* terrain);

	/**
	* @brief Water destructor.
	*/
	~Water() = default;

	/**
	* @brief Update water.
	*/
	void update(bool);

private:
	/**
	* @brief Reference to terrain vertices.
	*/
	TerrainVertices& terrainVertices;

	/**
	* @brief Copy of terrain vertices.
	*/
	TerrainVertices terrainVerticesCopy;

	/**
	* @brief Water level.
	*/
	float level;

	/**
	* @brief Minimum water level.
	*/
	float minimumLevel;

	/**
	* @brief Water level rise.
	*/
	float levelRise;

	/**
	* @brief Scale of terrain change.
	*/
	float scale;

	/**
	* @brief Max change
	*/
	float maxChange;
};