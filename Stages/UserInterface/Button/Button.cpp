#include "Button.hpp"

Button::Button()
	: isClicked(false), isCursorInsideArea(false)
{
}

void Button::setCallback(ButtonCallback callback)
{
	this->callback = callback;
}

void Button::mouseMove(int x, int y)
{
	this->isCursorInsideArea = this->checkIsCursorInsideArea(x, y);
}

void Button::mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (this->checkIsCursorInsideArea(x, y))
			{
				this->isClicked = !this->isClicked;
				this->callback(this->isClicked);
			}
		}
	}
}

void Button::setupTextures()
{
	if (this->textures.empty())
		return;

	if (this->textures.size() == 1)
		this->textures[0].bind(0);
	else
		this->textures[static_cast<unsigned>(this->isCursorInsideArea || this->isClicked)].bind(0);
}

inline bool Button::checkIsCursorInsideArea(int x, int y) const
{
	return (x >= this->vertices[0].position.x + this->position.x
		&& x <= this->vertices[2].position.x + this->position.x
		&& y >= this->vertices[0].position.y + this->position.y
		&& y <= this->vertices[2].position.y + this->position.y);
}
