#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Terrain.hpp"
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

	void rotateYaw(float);
	void rotatePitch(float);
	void updateCameraPosition(float&, float&, float);
	float inline getDistance(engine::Position point, engine::Normal& normal);
	bool inline pointAbovePlane(engine::Position&, engine::Position&, engine::Position&, engine::Position&);
	void rain();
	


	float yaw, pitch;
	Terrain* terrain;
	Water* water;
	engine::Chunk* chunk;
	engine::Texture texture;
	engine::Program terrainProgram, waterProgram, chunkProgram;
	engine::Shader meshVertexShader, particleVertexShader, chunkVertexShader,
		waterFragmentShader, terrainFragmentShader,  chunkFragmentShader,
		waterGeometryShader;
};