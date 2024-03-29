#include "Rain.hpp"

Rain::Rain()
	: engine::Particles(), isRaining(false)
{
	this->particles.resize(1000u);

	for (auto& particle : this->particles)
	{
		particle.lifespan = 0.0f;
	}
}

void Rain::run()
{
	// Particle life cycle.
	for (auto& particle : this->particles)
	{
		particle.lifespan -= 1.0f;
		if (particle.lifespan > 0.0f)
		{
			particle.velocity += particle.acceleration;
			particle.position += particle.velocity;
		}
	}
	
	// Create particles.
	if (this->isRaining)
	{
		constexpr unsigned renderSize = 3u;
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_real_distribution<float> distribution(-3.f, 3.f), y_distrubution(1.9f, 2.1f);

		unsigned i = 0u;
		for (auto& particle : this->particles)
		{
			if (particle.lifespan <= 0.0f)
			{
				particle.position.x = distribution(generator);
				particle.position.y = y_distrubution(generator);
				particle.position.z = distribution(generator);

				particle.lifespan = 100.0f;
				particle.acceleration = glm::vec3(0.0, -0.001, 0.0);
				particle.velocity = glm::vec3(0.0, -0.003, 0.0);
				if (i >= renderSize)
					break;
				else
					i++;
			}
		}
	}
}