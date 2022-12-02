#pragma once

#include <Mesh.hpp>
#include <functional>
#include <GL/glut.h>
#include <algorithm>

/**
* Terrain constructor.
*/
using Position2d = glm::vec2;

/**
* Terrain constructor.
*/
using Size = glm::vec2;

class Element : public engine::Mesh
{
public:
	/**
	* Terrain constructor.
	*/
	Element();
	/**
	* Terrain constructor.
	*/
	~Element() = default;

	/**
	* Terrain constructor.
	*/
	void setPosition(Position2d);

	/**
	* Terrain constructor.
	*/
	Position2d getPosition() const;

	/**
	* Terrain constructor.
	*/
	void setSize(Size);

	/**
	* Terrain constructor.
	*/
	Size getSize() const;

	/**
	* Terrain constructor.
	*/
	virtual void mouseMove(int, int) = 0;

	/**
	* Terrain constructor.
	*/
	virtual void mouseClick(int, int, int, int) = 0;
private:

	/**
	* Terrain constructor.
	*/
	Size size;
};