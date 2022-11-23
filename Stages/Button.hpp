#pragma once

#include <Mesh.hpp>
#include <functional>
#include <GL/glut.h>
#include <algorithm>

using ButtonCallback = std::function<void(bool)>;

class Button final : public engine::Mesh
{
public:
	/**
	* Terrain constructor.
	*/
	Button();
	~Button() = default;

	void setSize(engine::Size);

	void setCallback(ButtonCallback);

	void update(int, int, int, int);
private:
	ButtonCallback callback;
	bool isClicked;
	engine::Size size;
};