#include "StageManager.hpp"

StageManager::StageManager() : menu(this->options), presentation(this->options),
	currentStage(&this->menu)
{
	
}

void StageManager::Display()
{
	this->currentStage->Display();
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
	this->currentStage->OnKeyDown(key, x, y);
}

void StageManager::OnMouseClick(int button, int state, int x, int y)
{
	this->currentStage->OnMouseClick(button, state, x, y);
}

void StageManager::RefreshDisplay(int t)
{
	this->currentStage->RefreshDisplay(t);
}

void StageManager::Time(int t)
{
	this->currentStage->Time(t);
}
