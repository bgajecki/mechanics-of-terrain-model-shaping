#pragma once

#include <Mesh.hpp>
#include <algorithm>
#include <numeric>
#include <array>

class Water final : public engine::Mesh
{
public:
	/**
	* Water constructor.
	*/
	Water(engine::Mesh*);
	/**
	* Water destructor.
	*/
	~Water() = default;
	/**
	* Water work
	*/
	void update(bool);

private:
	std::vector<engine::MeshVertex>& terrainVertices;
	float level, minimumLevel, levelRise, scale;
};