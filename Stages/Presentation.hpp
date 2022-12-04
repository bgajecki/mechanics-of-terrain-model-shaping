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

/**
* @brief Presentation of mechanic on meshes.
*/
class Presentation final : public Stage, public engine::Scene
{
public:

	/**
	* @brief Presentation constructor.
	*/
	Presentation(engine::SceneManager& sceneManager, Options&);

	/**
	* @brief PresentationVoxel destructor.
	*/
	~Presentation() = default;

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;

	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void Motion(int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int dt) override final;

	virtual void Time(int dt) override final;

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
	* @brief Terrain mesh.
	*/
	Terrain* terrain;

	/**
	* @brief Rain effect.
	*/
	Rain* rain;

	/**
	* @brief Water plane and it's impact on the terrain.
	*/
	Water* water;

	/**
	* @brief Skybox responsible for the passage of time.
	*/
	Skybox* skybox;
	/**
	* @brief Presentation constructor.
	*/
	engine::Texture texture;

	/**
	* @brief Texture of RainOff button.
	*/
	engine::Texture rainOffTexture;

	/**
	* @brief Texture of RainOff button.
	*/
	engine::Texture rainOnTexture;

	/**
	* @brief Texture of the sky.
	*/
	engine::Texture skyTexture;

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
	* @brief Terrain program contains mesh vertex, tessellation control, tessellation evaluation and fragment shaders.
	*/
	engine::Program terrainProgram;

	/**
	* @brief Rain program contains rain vertex, fragment and geometry shaders.
	*/
	engine::Program rainProgram;

	/**
	* @brief Water program contains mesh vertex, tessellation control, water tessellation evaluation and water fragment shaders.
	*/
	engine::Program waterProgram;
	
	/**
	* @brief Skybox program contains simply vertex and fragment shaders.
	*/
	engine::Program skyboxProgram;

	/**
	* @brief User interface.
	*/
	UserInterface userInterface;

	/**
	* @brief Limitation for too fast presentation work.
	*/
	int timeLimit;

	/**
	* @brief Time pausue.
	*/
	bool pause;

	/**
	* @brief Rotation angle to imitate water flow.
	*/
	float rotationAngle;
};