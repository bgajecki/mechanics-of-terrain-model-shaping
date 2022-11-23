#pragma once

#include <Mesh.hpp>
#include <algorithm>
#include <numeric>

class Water final : public engine::Mesh
{
public:
	/**
	* Terrain constructor.
	*/
	Water(engine::Mesh*);
	/**
	* Terrain constructor.
	*/
	~Water() = default;
	/**
	* Terrain constructor.
	*/
	void update(bool);
private:
	std::vector<engine::MeshVertex>& terrainVertices;
	float level, minimumLevel, levelRise, scale;
};