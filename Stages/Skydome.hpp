#pragma once

#include <Mesh.hpp>
#include <algorithm>

class Skydome final : public engine::Mesh
{
public:
	/**
	* Terrain constructor.
	*/
	Skydome();
	~Skydome() = default;

	virtual engine::Matrix getModelMatrix() const override;

private:

};