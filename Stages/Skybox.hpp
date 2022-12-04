#pragma once

#include <Mesh.hpp>
#include <algorithm>

/**
* @brief Skybox representing day'n'night cycle.
*/
class Skybox final : public engine::Mesh
{
	/**
	* @brief Number of lights.
	*/
	static constexpr size_t NUMBER_OF_LIGHTS = 2u;

	/**
	* @brief Array of lights.
	*/
	using LightArray = std::array<engine::Position, Skybox::NUMBER_OF_LIGHTS>;
public:
	/**
	* @brief Skybox constructor.
	*/
	Skybox();

	/**
	* @brief Skybox destructor.
	*/
	~Skybox() = default;

	virtual engine::Matrix getModelMatrix() const override;

	/**
	* @brief Get lights.
	* @return Lights array data.
	*/
	const float* getLights() const;

	/**
	* @brief Get number of lights.
	* @return Number of lights.
	*/
	size_t getNumberOfLights() const;

	/**
	* @brief Update skybox.
	*/
	void update();
	
private:
	/**
	* @brief Lights container.
	*/
	LightArray lights;

	/**
	* @brief Current rotation of skybox.
	*/
	engine::Angle rotation;
};