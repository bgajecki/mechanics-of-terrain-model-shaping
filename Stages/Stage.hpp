#pragma once

/**
* @brief Interface class for stage.
*/
class Stage
{
public:
	/**
	* @brief Responsible for displaying screen.
	*/
	virtual void Display() = 0;

	/**
	* @brief Fit the changed screen size.
	* @param width New width of screen size.
	* @param height New height of screen size.
	*/
	virtual void Reshape(int width, int height) = 0;

	/**
	* @brief Special keyboard callback.
	* @param key The code of the pressed key on the keyboard.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void Special(int key, int x, int y) = 0;

	/**
	* @brief Keyboard callback.
	* @param key The code of the pressed key on the keyboard.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void OnKeyDown(unsigned char key, int x, int y) = 0;

	/**
	* @brief Motion callback.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void Motion(int x, int y) = 0;

	/**
	* @brief Mouse callback.
	* @param button The code of the pressed key on the mouse.
	* @param state Clicked or released.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void OnMouseClick(int button, int state, int x, int y) = 0;

	/**
	* @brief Timer callback responsible for refreshing display screen.
	* @param dt Time period.
	*/
	virtual void RefreshDisplay(int dt) = 0;

	/**
	* @brief Timer callback resposible for operation of the application.
	* @param dt Time period.
	*/
	virtual void Time(int dt) = 0;
};