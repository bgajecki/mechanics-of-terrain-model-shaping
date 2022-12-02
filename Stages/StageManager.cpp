#include "StageManager.hpp"

StageManager::StageManager()
{
	this->setOptions();
	this->menu = this->createScene<Menu>(options);
	this->presentation = this->createScene<Presentation>(options);
	this->presentationVoxel = this->createScene<PresentationVoxel>(options);
	this->linkPrograms();
	this->deleteShaders();
	this->setCurrentStageToMenu();
}

void StageManager::Display()
{
	this->draw();
}

void StageManager::Reshape(int width, int height)
{
	this->currentStage->Reshape(width, height);
}

void StageManager::Special(int key, int x, int y)
{
	this->currentStage->Special(key, x, y);
}

void StageManager::OnKeyDown(unsigned char key, int x, int y)
{
	key == 27 ? this->setCurrentStageToMenu() : this->currentStage->OnKeyDown(key, x, y);
}

void StageManager::Motion(int x, int y)
{
	this->currentStage->Motion(x, y);
}

void StageManager::OnMouseClick(int button, int state, int x, int y)
{
	this->currentStage->OnMouseClick(button, state, x, y);
}

void StageManager::RefreshDisplay(int t)
{
	this->currentStage->RefreshDisplay(t);
}

void StageManager::Time(int dt)
{
	this->currentStage->Time(dt);
}

void StageManager::setCurrentStageToMenu()
{
	this->currentScene = this->menu;
	this->currentStage = this->menu;
}

void StageManager::setCurrentStageToPresentation()
{
	this->currentScene = this->presentation;
	this->currentStage = this->presentation;
}

void StageManager::setCurrentStageToPresentationVoxel()
{
	this->currentScene = this->presentationVoxel;
	this->currentStage = this->presentationVoxel;
}

void StageManager::setOptions()
{
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW); // Left arrow
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT, GL_LINE);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 3u);

	this->options.width = glutGet(GLUT_SCREEN_WIDTH);
	this->options.height = glutGet(GLUT_SCREEN_HEIGHT);
	this->options.stageSetter = this;
}
