#pragma once

#include <Mesh.hpp>
#include <algorithm>

class Skybox final : public engine::Mesh
{
	static constexpr size_t NUMBER_OF_LIGHTS = 2u;

	using LightArray = std::array<engine::Position, Skybox::NUMBER_OF_LIGHTS>;
public:
	/**
	* Terrain constructor.
	*/
	Skybox();
	~Skybox() = default;



	virtual engine::Matrix getModelMatrix() const override;
	const float* getLights() const;
	size_t getNumberOfLights() const;
	void update();
	
private:
	LightArray lights;
	engine::Angle rotation;
};