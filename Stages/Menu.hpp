#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Options.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

class Menu final : public Stage,  public engine::Scene
{
public:
	/**
	* Menu constructor.
	*/
	Menu(engine::SceneManager& sceneManager, Options& options);
	~Menu() = default;

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;

	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

private:

	Options& options;
	//engine::Mesh* mesh;
	//engine::Texture texture;
	engine::Program program;
	engine::Shader vertexShader, fragmentShader;
};