#pragma once

#include <Particles.hpp>
#include <random>
/**
* @brief Rain effect based on particles.
*/
class Rain final : public engine::Particles
{
public:
	/**
	* @brief Rain effect constructor.
	*/
	Rain();

	/**
	* @brief Rain effect destructor.
	*/
	~Rain() = default;

	/**
	* @brief Cyclic function.
	*/
	void run();

	/**
	* @brief Is raining.
	*/
	bool isRaining;
};