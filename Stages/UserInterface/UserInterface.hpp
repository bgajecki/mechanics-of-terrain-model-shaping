#pragma once

#include "Button.hpp"

/**
* @brief User interface class. Observer user actions and let to know their elements.
*/
class UserInterface
{
	/**
	* @brief Vector of elements.
	*/
	using ElementVector = std::vector<Element*>;

public:
	/**
	* @brief UserInterface constructor.
	*/
	UserInterface();
	/**
	* @brief UserInterface destructor.
	*/
	~UserInterface() = default;

	/**
	* @brief Resize user interface and their elements.
	* @param width New width of user interface.
	* @param height New height of user interface.
	*/
	void resize(float width, float height);

	/**
	* @brief Set program of shaders.
	* @param program Program of the shaders.
	*/
	void setProgram(const engine::Program& program);

	/**
	* @brief Add a new element to user interface.
	* @tparam Type of the element
	* @param element Pointer to the element.
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
	* @brief Activated after mouse move.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	void mouseMove(int x, int y);

	/**
	* @brief Activated after mouse click.
	* @param button The code of the pressed key on the mouse.
	* @param state Clicked or released.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	void mouseClick(int button, int state, int x, int y);

protected:
	/**
	* @brief Return width scaled by passed parameter.
	* @param scale Scale level.
	* @return Scaled width.
	*/
	int widthScaling(float scale) const;

	/**
	* @brief Return height scaled by passed parameter.
	* @param scale Scale level.
	* @return Scaled height.
	*/
	int heightScaling(float scale) const;

	/**
	* @brief Return scale from scaled width.
	* @param scaledWidth Scaled width.
	* @return Scale.
	*/
	float getWidthScale(float scaledWidth) const;

	/**
	* @brief Return scale from scaled height.
	* @param scaledHeight Scaled height.
	* @return Scale.
	*/
	float getHeightScale(float scaledHeight) const;

	/**
	* @brief Program of the shaders.
	*/
	engine::Program program;

	/**
	* @brief Projection matrix.
	*/
	engine::Matrix projection;

	/**
	* @brief View matrix.
	*/
	engine::Matrix view;

	/**
	* @brief Elements container.
	*/
	ElementVector elements;

	/**
	* @brief Width of user interface.
	*/
	float width;

	/**
	* @brief Height of user interface.
	*/
	float height;
};