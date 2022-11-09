#include "Presentation.hpp"


Presentation::Presentation(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options)
{

	//meshVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/mesh.vs");
	//particleVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/particle.vs");
	//terrainFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/terrain.fs");
	//waterGeometryShader = sceneManager.createShader(GL_GEOMETRY_SHADER, "./shaders/water.gs");
	//waterFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/water.fs");

	chunkVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/chunk.vs");
	chunkFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/chunk.fs");
	

	//terrainProgram = sceneManager.createProgram();
	//waterProgram = sceneManager.createProgram();
	chunkProgram = sceneManager.createProgram();

	//terrainProgram->addShader(meshVertexShader);
	//terrainProgram->addShader(terrainFragmentShader);

	//waterProgram->addShader(particleVertexShader);
	//waterProgram->addShader(waterGeometryShader);
	//waterProgram->addShader(waterFragmentShader);

	chunkProgram->addShader(chunkVertexShader);
	chunkProgram->addShader(chunkFragmentShader);
	
	sceneManager.linkPrograms();
	sceneManager.deleteShaders();

	float height = glutGet(GLUT_SCREEN_HEIGHT);
	float width = glutGet(GLUT_SCREEN_WIDTH);

	this->projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 100.0f);

	this->camera.eye = { 0.0f, 0.5f, 0.5f };
	yaw = 0.f;
	pitch = 0.f;
	//this->camera.center.x = cos(this->pitch) * cos(this->yaw);
	//this->camera.center.y = sin(this->yaw);
	//this->camera.center.z = sin(this->pitch) * cos(this->yaw);
	this->camera.center = { 0.0f, 0.0f, 0.0f };
	this->camera.up = { 0.0f, 1.0f, 0.0 };
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);

	this->updateMvpMatrix();

	//terrainProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);
	//terrainProgram->createUniform(glUniform1i, "textureSampler", 0);

	//waterProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);

	chunkProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);

	/*
	terrain = this->createObject<Terrain>();
	texture.load("./textures/texture.jpg");
	terrain->textures.push_back(texture);
	terrain->program = terrainProgram;


	water = this->createObject<Water>();
	water->program = waterProgram;

	*/
	chunk = this->createObject<engine::Chunk>();
	chunk->createCube({ 0.0f, 0.0f, 0.0f });
	chunk->program = chunkProgram;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Presentation::Display()
{
}

void Presentation::Reshape(int width, int height)
{
}

void Presentation::Special(int key, int x, int y)
{
	const float two_degrees = 0.034906585f;
	switch (key)
	{
	case GLUT_KEY_UP:
		this->rotateYaw(two_degrees);
		break;
	case GLUT_KEY_DOWN:
		this->rotateYaw(-two_degrees);
		break;
	case GLUT_KEY_LEFT:
		this->rotatePitch(-two_degrees);
		break;
	case GLUT_KEY_RIGHT:
		this->rotatePitch(two_degrees);
		break;
	}

}

void Presentation::OnKeyDown(unsigned char key, int x, int y)
{
	float update = 0.1f;
	switch (key)
	{
	case 'q':
		updateCameraPosition(this->camera.center.z, this->camera.eye.z, update);
		break;
	case 'e':
		updateCameraPosition(this->camera.center.z, this->camera.eye.z, -update);
		break;
	case 'w':
		updateCameraPosition(this->camera.center.y, this->camera.eye.y, update);
		break;
	case 's':
		updateCameraPosition(this->camera.center.y, this->camera.eye.y, -update);
		break;
	case 'a':
		updateCameraPosition(this->camera.center.x, this->camera.eye.x, -update);
		break;
	case 'd':
		updateCameraPosition(this->camera.center.x, this->camera.eye.x, update);
		break;
	}


}

void Presentation::OnMouseClick(int button, int state, int x, int y)
{
}

void Presentation::RefreshDisplay(int t)
{
}

void Presentation::Time(int t)
{
	//this->rain();
}

void Presentation::rotateYaw(float angle)
{
	const float full_turn = 6.28318530718f;
	this->yaw += angle;
	if (this->yaw > full_turn)
		this->yaw = 0.f;
	else if (this->yaw < -full_turn)
		this->yaw = 0.f;
	this->camera.center.x = cos(this->pitch) * cos(this->yaw);
	this->camera.center.y = sin(this->yaw);
	this->camera.center.z = sin(this->pitch) * cos(this->yaw);
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}

void Presentation::rotatePitch(float angle)
{
	const float full_turn = 6.28318530718f;
	this->pitch += angle;
	if (this->pitch > full_turn)
		this->pitch = 0.f;
	else if (this->pitch < -full_turn)
		this->pitch = 0.f;
	this->camera.center.x = cos(this->pitch) * cos(this->yaw);
	this->camera.center.z = sin(this->pitch) * cos(this->yaw);
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}

void Presentation::updateCameraPosition(float& center, float& eye, float update)
{
	center += update;
	eye += update;
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}


inline float Presentation::getDistance(engine::Position point, engine::Normal& normal)
{
	float distance = normal.x * point.x + normal.y * point.y + normal.z * point.z;
	distance = glm::abs(distance);
;	return distance;
}

inline bool Presentation::pointAbovePlane(engine::Position& a, engine::Position& b, engine::Position& c, engine::Position& point)
{
	engine::Position min, max;
	min = glm::min(a, b);
	min = glm::min(min, c);
	max = glm::max(a, b);
	max = glm::max(max, c);
	if (min.x <= point.x && max.x >= point.x && min.z <= point.z && max.z >= point.z)
		return true;
	return false;
}

void Presentation::rain()
{
	for (auto& particle : this->water->particles)
	{
		particle.lifespan -= 1.0f;
		if (particle.lifespan > 0.0f)
		{
			engine::Vertex a, b, c;
			bool point_above_plane = false;
			for (size_t i = 0u; i < this->terrain->indices.size(); i += 3u)
			{
				a = this->terrain->vertices[this->terrain->indices[i]];
				b = this->terrain->vertices[this->terrain->indices[i + 1]];
				c = this->terrain->vertices[this->terrain->indices[i + 2]];
				float distance = 0.0f;
				point_above_plane = this->pointAbovePlane(a.position, b.position, c.position, particle.position);
				if (point_above_plane)
				{
					distance = this->getDistance(particle.position, a.normal);
					if (distance > 0.008)
					{
						particle.velocity += particle.acceleration;
						distance = this->getDistance(particle.position + particle.velocity, a.normal);
						if (distance > 0.1)
							particle.position += particle.velocity;
						else
							particle.position.y -= distance;
					}
					break;
				}
			}
			if (!point_above_plane)
			{
				particle.velocity += particle.acceleration;
				particle.position += particle.velocity;
			}
		}
	}
	const unsigned howMuch = 2u;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(-1.f, 1.f), y_distrubution(1.9f, 2.1f);

	unsigned i = 0u;
	for (auto& particle : this->water->particles)
	{
		if (particle.lifespan <= 0.0f)
		{
			particle.position.x = distribution(generator);
			particle.position.y = y_distrubution(generator);
			particle.position.z = distribution(generator);

			particle.lifespan = 100.0f;
			particle.acceleration = glm::vec3(0.0, -0.001, 0.0);
			particle.velocity = glm::vec3(0.0, -0.003, 0.0);
			if (i >= howMuch)
				break;
			else
				i++;
		}
	}
}
