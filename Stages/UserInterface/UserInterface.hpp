#pragma once

#include "Button.hpp"

class UserInterface
{
public:
	/**
	* Terrain constructor.
	*/
	UserInterface();
	/**
	* Terrain constructor.
	*/
	~UserInterface() = default;

	/**
	* Terrain constructor.
	*/
	void resize(float, float);

	/**
	* Terrain constructor.
	*/
	void setProgram(const engine::Program&);

	/**
	* Draw mesh
	*/
	template<typename T>
	void add(T* element)
	{
		this->elements.push_back(element);
		Element* last_element = this->elements[this->elements.size() - 1u];
		last_element->setProgram(this->program);
		Size size = last_element->getSize();
		last_element->setSize({ this->widthScaling(size.x), this->heightScaling(size.y) });
		Position2d position = last_element->getPosition();
		last_element->setPosition({ this->widthScaling(position.x), this->heightScaling(position.y) });
	}

	/**
	* Terrain constructor.
	*/
	void mouseMove(int, int);

	/**
	* Terrain constructor.
	*/
	void mouseClick(int, int, int, int);
protected:
	/**
	* Terrain constructor.
	*/
	float widthScaling(float) const;
	/**
	* Terrain constructor.
	*/
	float heightScaling(float) const;
	/**
	* Terrain constructor.
	*/
	float getWidthScale(float) const;
	/**
	* Terrain constructor.
	*/
	float getHeightScale(float) const;

	/**
	* Terrain constructor.
	*/
	engine::Program program;
	/**
	* Terrain constructor.
	*/
	engine::Matrix projection;
	/**
	* Terrain constructor.
	*/
	engine::Matrix view;
	/**
	* Terrain constructor.
	*/
	std::vector<Element*> elements;

	/**
	* Terrain constructor.
	*/
	float width;

	/**
	* Terrain constructor.
	*/
	float height;
};