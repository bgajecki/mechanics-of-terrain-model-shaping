#pragma once

/**
* @brief Interface class created for stage chaning.
*/
class StageSetter
{
public:
	/**
	* @brief Set current stage to menu.
	*/
	virtual void setCurrentStageToMenu() = 0;

	/**
	* @brief Set current stage to mechanic presentation on meshes.
	*/
	virtual void setCurrentStageToPresentation() = 0;

	/**
	* @brief Set current stage to mechanic presentation on voxels.
	*/
	virtual void setCurrentStageToPresentationVoxel() = 0;
};