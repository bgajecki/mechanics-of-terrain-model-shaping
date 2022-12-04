#pragma once

#include <Mesh.hpp>
#include <functional>
#include <GL/glut.h>
#include <algorithm>

/**
* @brief Type of 2D position of the user interface element.
*/
using Position2d = glm::vec2;

/**
* @brief Type of 2D size of the user interface element.
*/
using Size = glm::vec2;

/**
* @brief User interface element class.
*/
class Element : public engine::Mesh
{
public:
	/**
	* Element constructor.
	*/
	Element();

	/**
	* Element destructor.
	*/
	~Element() = default;

	/**
	* @brief Set element position.
	* @param position New element position.
	*/
	void setPosition(Position2d position);

	/**
	* @brief Get element position.
	* @return Element position.
	*/
	Position2d getPosition() const;

	/**
	* @brief Set element size.
	* @param position New element size.
	*/
	void setSize(Size);

	/**
	* @brief Get element size.
	* @return Element size.
	*/
	Size getSize() const;

	/**
	* @brief Activated after mouse move.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void mouseMove(int x, int y);

	/**
	* @brief Activated after mouse click.
	* @param button The code of the pressed key on the mouse.
	* @param state Clicked or released.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void mouseClick(int button, int state, int x, int y);

private:

	/**
	* 2D size of the user interface element.
	*/
	Size size;
};