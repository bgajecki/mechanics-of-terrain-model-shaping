#include "UserInterface.hpp"
#include "UserInterface.hpp"

UserInterface::UserInterface()
	: width(0.0f), height(0.0f), projection(1)
{
	this->view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void UserInterface::mouseMove(int x, int y)
{
	for (auto& element : this->elements)
		element->mouseMove(x, y);
}

void UserInterface::mouseClick(int button, int state, int x, int y)
{
	for (auto& element : this->elements)
		element->mouseClick(button, state, x, y);
}

float UserInterface::widthScaling(float scale) const
{
	return scale * this->width;;
}

float UserInterface::heightScaling(float scale) const
{
	return scale * this->height;
}

float UserInterface::getWidthScale(float scaledWidth) const
{
	return scaledWidth / this->width;
}

float UserInterface::getHeightScale(float scaledHeight) const
{
	return scaledHeight / this->height;
}

void UserInterface::resize(float width, float height)
{
	for (auto& element : this->elements)
	{
		Size size = element->getSize();
		element->setSize({ this->getWidthScale(size.x), this->getHeightScale(size.y) });
		Position2d position = element->getPosition();
		element->setPosition({ this->getWidthScale(position.x), this->getHeightScale(position.y) });
	}

	this->width = width;
	this->height = height;
	this->projection = glm::ortho(0.0f, width, height, 0.0f, 0.0f, 2.0f);

	for (auto& element : this->elements)
	{
		Size size = element->getSize();
		element->setSize({ this->widthScaling(size.x), this->heightScaling(size.y) });
		Position2d position = element->getPosition();
		element->setPosition({ this->widthScaling(position.x), this->heightScaling(position.y) });
	}
}

void UserInterface::setProgram(const engine::Program& program)
{
	this->program = program;
	this->program->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->program->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->program->createUniform(glUniform1i, "textureSampler", 0);
}