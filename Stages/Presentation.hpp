#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Terrain.hpp"
#include "Rain.hpp"
#include "Water.hpp"
#include "Options.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <GL/glut.h>
#include <random>
#include <Chunk.hpp>



class Presentation final : public Stage, public engine::Scene
{
public:

	/**
	* Presentation constructor.
	*/
	Presentation(engine::SceneManager& sceneManager, Options&);

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;

	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

private:
	Options& options;
	Terrain* terrain;
	Rain* rain;
	Water* water;
	engine::Texture texture;
	engine::Program terrainProgram, rainProgram, waterProgram;
	engine::Shader meshVertexShader, rainVertexShader,
		rainFragmentShader, terrainFragmentShader, waterFragmentShader,
		rainGeometryShader;
};