#pragma once

/**
* @brief Abstrac class for stage.
*/
class Stage
{
public:
	/**
	* Responsible for displaying screen.
	*/
	virtual void Display() {};

	/**
	* Fit the changed screen size.
	* @param width New width of screen size.
	* @param height New height of screen size.
	*/
	virtual void Reshape(int width, int height) {};

	/**
	* Special keyboard callback.
	* @param key The code of the pressed key on the keyboard.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void Special(int key, int x, int y) {};

	/**
	* Keyboard callback.
	* @param key The code of the pressed key on the keyboard.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void OnKeyDown(unsigned char key, int x, int y) {};

	/**
	* Mouse callback.
	* @param button  The code of the pressed key on the mouse.
	* @param state Clicked or released.
	* @param x Horizontal cursor position.
	* @param y Vertical cursor position.
	*/
	virtual void OnMouseClick(int button, int state, int x, int y) {};

	/**
	* Timer callback responsible for refreshing display screen.
	* @param t Time period.
	*/
	virtual void RefreshDisplay(int t) {};

	/**
	* Timer callback resposible for operation of the application.
	* @param t Time period.
	*/
	virtual void Time(int t) {};
};