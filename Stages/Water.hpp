#pragma once

#include <Particles.hpp>
#include <random>

class Water final : public engine::Particles
{
public:
	/**
	* Water constructor.
	*/
	Water();
	~Water() = default;

	void rain();
private:
};