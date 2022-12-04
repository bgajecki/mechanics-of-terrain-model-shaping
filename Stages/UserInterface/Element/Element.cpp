#include "Element.hpp"

Element::Element()
	: size(0.0f, 0.0f)
{
	this->vertices.reserve(4u);
	this->indices.push_back(0);
	this->indices.push_back(0 + 1);
	this->indices.push_back(0 + 2);

	this->indices.push_back(0);
	this->indices.push_back(0 + 2);
	this->indices.push_back(0 + 3);
	std::reverse(this->indices.begin(), this->indices.end());
}

void Element::setPosition(Position2d size)
{
	this->position.x = size.x;
	this->position.y = size.y;
	this->position.z = -1.0f;
}

Position2d Element::getPosition() const
{
	return { this->position.x, this->position.y };
}

void Element::setSize(Size size)
{
	this->size = size;
	this->vertices.clear();
	engine::MeshVertex vertex;
	vertex.position = engine::Position(-this->size.x / 2.0f, -this->size.y / 2.0f, 0.0f);
	vertex.normal = engine::Normal(0.0f, 0.0f, 1.0f);
	vertex.attribute = engine::TextureCoordinate(0.0f, 0.0f);
	this->vertices.push_back(vertex);
	vertex.position = engine::Position(this->size.x / 2.0f, -this->size.y / 2.0f, 0.0f);
	vertex.attribute = engine::TextureCoordinate(1.0f, 0.0f);
	this->vertices.push_back(vertex);
	vertex.position = engine::Position(this->size.x / 2.0f, this->size.y / 2.0f, 0.0f);
	vertex.attribute = engine::TextureCoordinate(1.0f, 1.0f);
	this->vertices.push_back(vertex);
	vertex.position = engine::Position(-this->size.x / 2.0f, this->size.y / 2.0f, 0.0f);
	vertex.attribute = engine::TextureCoordinate(0.0f, 1.0f);
	this->vertices.push_back(vertex);
}

Size Element::getSize() const
{
	return this->size;
}

void Element::mouseMove(int x, int y)
{
}

void Element::mouseClick(int button, int state, int x, int y)
{
}
