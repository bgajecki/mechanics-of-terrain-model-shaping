#pragma once

#include <Mesh.hpp>

/**
* @brief Mesh class for terrain.
*/
class Terrain final : public engine::Mesh
{
public:
	/**
	* @brief Terrain constructor.
	*/
	Terrain();

	/**
	* @brief Terrain destructor.
	*/
	~Terrain() = default;
};