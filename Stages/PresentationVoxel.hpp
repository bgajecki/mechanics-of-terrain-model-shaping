#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Options.hpp"
#include "World.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <GL/glut.h>




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

	void rotateYaw(float);
	void rotatePitch(float);
	void updateCameraPosition(float&, float&, float);
	
	float yaw, pitch;
	engine::Program chunkProgram;
	engine::Shader chunkVertexShader, chunkFragmentShader;
	World* world;
};