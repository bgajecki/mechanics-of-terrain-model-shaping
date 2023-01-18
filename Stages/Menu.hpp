#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Options.hpp"
#include "UserInterface.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut.h>

/**
* @brief Menu of application.
*/
class Menu final : public Stage,  public engine::Scene, public UserInterface
{
public:
	/**
	* @brief Menu constructor.
	*/
	Menu(engine::SceneManager& sceneManager, Options& options);

	/**
	* @brief Menu destructor.
	*/
	~Menu() = default;

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
	* @brief Options for the all stages.
	*/
	Options& options;

	/**
	* @brief Texture of mesh presentation button.
	*/
	engine::Texture presentationMeshTexture;

	/**
	* @brief Texture of voxel presentation button.
	*/
	engine::Texture presentationVoxelTexture;

	/**
	* @brief Texture of exit button.
	*/
	engine::Texture exitTexture;

	/**
	* @brief Texture of background.
	*/
	engine::Texture backgroundTexture;

	/**
	* @brief Texture of activated mesh presentation button.
	*/
	engine::Texture presentationMeshActiveTexture;

	/**
	* @brief Texture of activated voxel presentation button.
	*/
	engine::Texture presentationVoxelActiveTexture;

	/**
	* @brief Texture of activated exit button.
	*/
	engine::Texture exitActiveTexture;
};