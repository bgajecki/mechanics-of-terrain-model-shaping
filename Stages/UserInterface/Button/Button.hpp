#pragma once

#include "Element.hpp"

/**
* Terrain constructor.
*/
using ButtonCallback = std::function<void(bool&)>;

class Button final : public Element
{
public:
	/**
	* Terrain constructor.
	*/
	Button();
	/**
	* Terrain constructor.
	*/
	~Button() = default;

	/**
	* Terrain constructor.
	*/
	void setCallback(ButtonCallback);

	/**
	* Terrain constructor.
	*/
	virtual void mouseMove(int, int) override;

	/**
	* Terrain constructor.
	*/
	virtual void mouseClick(int, int, int, int) override;


private:
	/**
	* Terrain constructor.
	*/
	virtual void setupTextures() override;

	/**
	* Terrain constructor.
	*/
	inline bool checkIsCursorInsideArea(int, int) const;

	/**
	* Terrain constructor.
	*/
	ButtonCallback callback;

	/**
	* Terrain constructor.
	*/
	bool isClicked;

	/**
	* Terrain constructor.
	*/
	bool isCursorInsideArea;
};