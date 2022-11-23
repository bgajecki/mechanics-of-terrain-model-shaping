#include "Skydome.hpp"

Skydome::Skydome()
	: engine::Mesh()
{
	this->loadObj("./objects/skydome.obj");
	std::reverse(this->indices.begin(), this->indices.end());
}

engine::Matrix Skydome::getModelMatrix() const
{
	engine::Matrix model = Object::getModelMatrix();
	model = glm::scale(model, glm::vec3(5.0f));
	return model;
}
