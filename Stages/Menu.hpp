#pragma once

#include <Scene.hpp>
#include "Stage.hpp"
#include "Options.hpp"
#include "UserInterface.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut.h>

class Menu final : public Stage,  public engine::Scene, public UserInterface
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

	virtual void Motion(int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int dt) override final;

	virtual void Time(int dt) override final;

private:
	/**
	* Presentation constructor.
	*/
	void initializeShaders();

	/**
	* Presentation constructor.
	*/
	void initializeUserInterface();

	/**
	* Presentation constructor.
	*/
	Options& options;

	/**
	* Presentation constructor.
	*/
	engine::Texture presentationMeshTexture;
	/**
	* Presentation constructor.
	*/
	engine::Texture presentationVoxelTexture;
	/**
	* Presentation constructor.
	*/
	engine::Texture exitTexture;
	/**
	* Presentation constructor.
	*/
	engine::Texture backgroundTexture;

	/**
	* Presentation constructor.
	*/
	engine::Texture presentationMeshActiveTexture;
	/**
	* Presentation constructor.
	*/
	engine::Texture presentationVoxelActiveTexture;
	/**
	* Presentation constructor.
	*/
	engine::Texture exitActiveTexture;

	/**
	* Presentation constructor.
	*/
	GLint textureSampler;
};