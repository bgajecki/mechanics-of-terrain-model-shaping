#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Options.hpp"
#include "World.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <GL/glut.h>
#include "Skydome.hpp"
#include "Button.hpp"

class PresentationVoxel final : public Stage, public engine::Scene
{
public:

	/**
	* Presentation constructor.
	*/
	PresentationVoxel(engine::SceneManager&, Options&);

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;

	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

private:
	Options& options;
	engine::Texture skyTexture, buttonTexture;
	engine::Program chunkProgram, skydomeProgram, userInterfaceProgram;
	engine::Shader chunkVertexShader, chunkFragmentShader, meshVertexShader, skydomeFragmentShader, userInterfaceVertexShader, userInterfaceFragmentShader;
	Button* button;
	World* world;
	Skydome* skydome;
	engine::Matrix userInterfaceProjection;
};