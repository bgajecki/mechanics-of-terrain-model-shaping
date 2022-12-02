#pragma once

#include <Particles.hpp>
#include <random>

class Rain final : public engine::Particles
{
public:
	/**
	* Water constructor.
	*/
	Rain();

	/**
	* Water constructor.
	*/
	~Rain() = default;


	/**
	* Water constructor.
	*/
	void run();

	/**
	* Water constructor.
	*/
	bool isRaining;
};