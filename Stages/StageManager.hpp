#pragma once

#include "Menu.hpp"
#include "Presentation.hpp"
#include "PresentationVoxel.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
/**
* @brief A stage manager class that manages program stages.
* 
* Stage manager have two stages,
* the first one for menu and the second one for mechanic presentation.
*/
class StageManager final : public Stage, public engine::SceneManager
{
public:
	/**
	* StageManager constructor.
	*/
	StageManager();

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;
	
	void OnKeyDown(unsigned char key, int x, int y) override final;
	
	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

private:

	engine::SceneManager sceneManager;
	Options options;

	Stage* currentStage;

	Menu* menu;
	Presentation* presentation;
	PresentationVoxel* presentationVoxel;
};