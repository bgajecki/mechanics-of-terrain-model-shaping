#include "Water.hpp"

Water::Water()
	: engine::Particles()
{
	this->particles.resize(1000u);

	for (auto& particle : this->particles)
	{
		particle.lifespan = 0.0f;
	}
}

void Water::rain()
{

}