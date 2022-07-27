#pragma once

#include "Menu.hpp"
#include "Presentation.hpp"
#include "Options.hpp"

/**
* @brief A stage manager class that manages program stages.
* 
* Stage manager have two stages,
* the first one for menu and the second one for mechanic presentation.
*/
class StageManager : public Stage
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
	Menu menu;
	Presentation presentation;
	Options options;
	Stage* currentStage;
};