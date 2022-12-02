#pragma once

#include "Menu.hpp"
#include "Presentation.hpp"
#include "PresentationVoxel.hpp"

/**
* @brief A stage manager class that manages program stages.
* 
* Stage manager have three stages,
* the first one for menu, the second one for mechanic presentation on meshes
* and the third one for mechanic presentation on voxels.
*/
class StageManager final : public Stage, public StageSetter, public engine::SceneManager
{
public:
	/**
	* StageManager constructor.
	*/
	StageManager();

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;
	
	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void Motion(int x, int y) override final;
	
	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

	virtual void setCurrentStageToMenu() override;

	virtual void setCurrentStageToPresentation() override;

	virtual void setCurrentStageToPresentationVoxel() override;

private:
	/**
	* Set options and prepare environment.
	*/
	void setOptions();
	
	/**
	* Options for the all stages.
	*/
	Options options;

	/**
	* Current stage pointer.
	*/
	Stage* currentStage;

	/**
	* Menu stage.
	*/
	Menu* menu;

	/**
	* Mechanic presentation on meshes.
	*/
	Presentation* presentation;

	/**
	* Mechanic presentation on voxels.
	*/
	PresentationVoxel* presentationVoxel;
};