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
	for (auto& particle : this->particles)
	{
		particle.lifespan -= 1.0f;
		if (particle.lifespan > 0.0f)
		{
			particle.velocity += particle.acceleration;
			particle.position += particle.velocity;
		}
	}
	
	if (this->isRaining)
	{
		const unsigned render_size = 3u;
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_real_distribution<float> distribution(-1.f, 1.f), y_distrubution(1.9f, 2.1f);

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
				if (i >= render_size)
					break;
				else
					i++;
			}
		}
	}
}