#pragma once

/**
* @brief Abstract class
* 
* Stage manager have two stages,
* the first one for menu and the second one for mechanic presentation.
*/
class StageSetter
{
public:
	/**
	* StageManager constructor.
	*/
	virtual void setCurrentStageToMenu() = 0;

	/**
	* StageManager constructor.
	*/
	virtual void setCurrentStageToPresentation() = 0;

	/**
	* StageManager constructor.
	*/
	virtual void setCurrentStageToPresentationVoxel() = 0;
};