#pragma once

#include "StageSetter.hpp"

/**
* @brief Storing application options.
*/
struct Options
{
	/**
	* @brief Current application width.
	*/
	float width;
	/**
	* @brief Current application height.
	*/
	float height;
	/**
	* @brief Pointer to the stageSetter class.
	*/
	StageSetter* stageSetter;
};