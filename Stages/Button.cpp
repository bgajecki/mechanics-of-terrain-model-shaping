#include "Button.hpp"

Button::Button()
	: engine::Mesh(), isClicked(false), size(0.0f, 0.0f)
{
	this->vertices.reserve(4u);
	this->indices.push_back(0);
	this->indices.push_back(0 + 1);
	this->indices.push_back(0 + 2);

	this->indices.push_back(0);
	this->indices.push_back(0 + 2);
	this->indices.push_back(0 + 3);
	//std::reverse(this->indices.begin(), this->indices.end());
}

void Button::setSize(engine::Size size)
{
	double max_x = 1.0, //static_cast<double>(GetSystemMetrics(SM_CXSCREEN)),
	max_y = 1.0;// static_cast<double>(GetSystemMetrics(SM_CYSCREEN));
	this->size = engine::Size(size.x / max_x, size.y / max_y);
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

void Button::setCallback(ButtonCallback callback)
{
	this->callback = callback;
}

void Button::update(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		double max_x = static_cast<double>(GetSystemMetrics(SM_CXSCREEN)) / 2.0,
			max_y = static_cast<double>(GetSystemMetrics(SM_CYSCREEN)) / 2.0;
		double float_x = (static_cast<double>(x) - max_x) / max_x,
			float_y = -((static_cast<double>(y) - max_y) / max_y);
		if (float_x >= this->vertices[0].position.x
			&& float_x <= this->vertices[2].position.x
			&& float_y >= this->vertices[0].position.y
			&& float_y <= this->vertices[2].position.y)
		{
			this->isClicked = !this->isClicked;
			this->callback(this->isClicked);
		}
	}
}
