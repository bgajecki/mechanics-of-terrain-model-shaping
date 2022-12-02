#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Options.hpp"
#include "World.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <GL/glut.h>
#include <array>
#include "Skybox.hpp"
#include "UserInterface/UserInterface.hpp"

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
	* Options for the all stages.
	*/
	Options& options;

	/**
	* Texture of the sky.
	*/
	engine::Texture skyTexture; 
	
	/**
	* Texture of RainOff button.
	*/
	engine::Texture rainOffTexture;

	/**
	* Texture of RainOn button.
	*/
	engine::Texture rainOnTexture;

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
	* Chunk program contains chunk vertex and fragment shaders.
	*/
	engine::Program chunkProgram;
	
	/**
	* Skybox program contains simply vertex and fragment shaders.
	*/
	engine::Program skyboxProgram;

	/**
	* User interface.
	*/
	UserInterface userInterface;

	/**
	* Single biom presenting mechanics of terrain model shaping using voxel technicues.
	*/
	World* world;

	/**
	* Skybox responsible for the passage of time.
	*/
	Skybox* skybox;

	/**
	* Limitation for too fast presentation work.
	*/
	int timeLimit;

	/**
	* Time pausue.
	*/
	bool pause;
};