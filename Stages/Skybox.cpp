#include "Skybox.hpp"

Skybox::Skybox()
	: engine::Mesh(), rotation(0.0f)
{
	this->loadObj("./objects/skybox.obj");
	std::reverse(this->indices.begin(), this->indices.end());
	this->lights[0] = glm::vec3(0.0f, 3.0f, 0.0f);
	this->lights[1] = glm::vec3(0.0f, -3.0f, 0.0f);
}

engine::Matrix Skybox::getModelMatrix() const
{
	engine::Matrix model = Object::getModelMatrix();
	model = glm::scale(model, glm::vec3(5.0f));
	model = glm::rotate(model, glm::radians(this->rotation), glm::vec3(0.0, 0.0, 1.0f));
	return model;
}

const float* Skybox::getLights() const
{
	return reinterpret_cast<const float*>(this->lights.data());
}

size_t Skybox::getNumberOfLights() const
{
	return this->NUMBER_OF_LIGHTS;
}

void Skybox::update()
{
	this->rotation = this->rotation > 359.0f ? 0.0f : this->rotation + 1.0f;

	engine::Matrix rotationMatrix(1);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(1.0f), glm::vec3(0.0, 0.0, 1.0f));
	for (auto& light : this->lights)
		light = rotationMatrix * glm::vec4(this->lights[0], 1.0f);
}
