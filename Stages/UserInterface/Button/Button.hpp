#pragma once

#include "Element.hpp"

/**
* @brief Type of function activated by clicking the mouse on the button.
*/
using ButtonCallback = std::function<void(bool&)>;

/**
* @brief User interface button class.
*/
class Button final : public Element
{
public:
	/**
	* @brief Button constructor.
	*/
	Button();
	/**
	* @brief Button destructor.
	*/
	~Button() = default;

	/**
	* @brief Set on mouse click callback.
	* @param callback Function activated by clicking the mouse on the button.
	*/
	void setCallback(ButtonCallback callback);

	virtual void mouseMove(int x, int y) override final;
	virtual void mouseClick(int button, int state, int x, int y) override final;


private:

	virtual void setupTextures() override final;

	/**
	* @brief Check is cursor inside button area.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	inline bool checkIsCursorInsideArea(int x, int y) const;

	/**
	* @brief Function activated by clicking the mouse on the button.
	*/
	ButtonCallback callback;

	/**
	* @brief Is button on or off.
	*/
	bool isClicked;

	/**
	* @brief Is cursor inside button area.
	*/
	bool isCursorInsideArea;
};