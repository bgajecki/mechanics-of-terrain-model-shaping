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


/**
* @brief Presentation of mechanic on voxels.
*/
class PresentationVoxel final : public Stage, public engine::Scene
{
public:
	/**
	* @brief PresentationVoxel constructor.
	*/
	PresentationVoxel(engine::SceneManager&, Options&);

	/**
	* @brief PresentationVoxel destructor.
	*/
	~PresentationVoxel() = default;

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;

	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void Motion(int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

private:
	
	/**
	* @brief Initialize shaders for futher use.
	*/
	void initializeShaders();

	/**
	* @brief Initialize user interface.
	*/
	void initializeUserInterface();

	/**
	* @brief Initialize objects.
	*/
	void initializeObjects();

	/**
	* @brief Options for the all stages.
	*/
	Options& options;

	/**
	* @brief Texture of the sky.
	*/
	engine::Texture skyTexture; 
	
	/**
	* @brief Texture of RainOff button.
	*/
	engine::Texture rainOffTexture;

	/**
	* @brief Texture of RainOn button.
	*/
	engine::Texture rainOnTexture;

	/**
	* @brief Texture of pause button.
	*/
	engine::Texture pauseTexture;

	/**
	* @brief Texture of play button.
	*/
	engine::Texture playTexture;

	/**
	* @brief Texture of playx2 button.
	*/
	engine::Texture playx2Texture;

	/**
	* @brief Texture of playx3 button.
	*/
	engine::Texture playx3Texture;

	/**
	* @brief Chunk program contains chunk vertex and fragment shaders.
	*/
	engine::Program chunkProgram;
	
	/**
	* @brief Skybox program contains simply vertex and fragment shaders.
	*/
	engine::Program skyboxProgram;

	/**
	* @brief User interface.
	*/
	UserInterface userInterface;

	/**
	* @brief Single biom presenting mechanics of terrain model shaping using voxel technicues.
	*/
	World* world;

	/**
	* @brief Skybox responsible for the passage of time.
	*/
	Skybox* skybox;

	/**
	* @brief Limitation for too fast presentation work.
	*/
	int timeLimit;

	/**
	* @brief Time pausue.
	*/
	bool pause;
};