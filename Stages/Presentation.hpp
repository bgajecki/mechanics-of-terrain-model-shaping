#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Terrain.hpp"
#include "Rain.hpp"
#include "Water.hpp"
#include "Skybox.hpp"
#include "Options.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <GL/glut.h>
#include <random>
#include "UserInterface.hpp"



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

	virtual void RefreshDisplay(int dt) override final;

	virtual void Time(int dt) override final;

private:
	/**
	* Initialize shaders for futher use.
	*/
	void initializeShaders();

	/**
	* Initialize user interface.
	*/
	void initializeUserInterface();

	/**
	* Initialize objects.
	*/
	void initializeObjects();

	/**
	* Presentation constructor.
	*/
	Options& options;

	/**
	* Terrain mesh.
	*/
	Terrain* terrain;

	/**
	* Rain effect.
	*/
	Rain* rain;

	/**
	* Water plane and it's impact on the terrain.
	*/
	Water* water;

	/**
	* Skybox responsible for the passage of time.
	*/
	Skybox* skybox;
	/**
	* Presentation constructor.
	*/
	engine::Texture texture;

	/**
	* Texture of RainOff button.
	*/
	engine::Texture rainOffTexture;

	/**
	* Texture of RainOff button.
	*/
	engine::Texture rainOnTexture;

	/**
	* Texture of the sky.
	*/
	engine::Texture skyTexture;

	/**
	* Texture of pause button.
	*/
	engine::Texture pauseTexture;

	/**
	* Texture of play button.
	*/
	engine::Texture playTexture;

	/**
	* Texture of playx2 button.
	*/
	engine::Texture playx2Texture;
	
	/**
	* Texture of playx3 button.
	*/
	engine::Texture playx3Texture;

	/**
	* Terrain program contains mesh vertex, tessellation control, tessellation evaluation and fragment shaders.
	*/
	engine::Program terrainProgram;

	/**
	* Rain program contains rain vertex, fragment and geometry shaders.
	*/
	engine::Program rainProgram;

	/**
	* Water program contains mesh vertex, tessellation control, water tessellation evaluation and water fragment shaders.
	*/
	engine::Program waterProgram;
	
	/**
	* Skybox program contains simply vertex and fragment shaders.
	*/
	engine::Program skyboxProgram;

	/**
	* User interface.
	*/
	UserInterface userInterface;

	/**
	* Limitation for too fast presentation work.
	*/
	int timeLimit;

	/**
	* Time pausue.
	*/
	bool pause;

	/**
	* Rotation angle to imitate water flow.
	*/
	float rotationAngle;
};