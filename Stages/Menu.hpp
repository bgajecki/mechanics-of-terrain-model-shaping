#pragma once

#include <ShaderManager.hpp>
#include "Stage.hpp"
#include "Options.hpp"

class Menu : public Stage
{
public:
	/**
	* Menu constructor.
	*/
	Menu(Options&);

	virtual void Display() override final;

	virtual void Reshape(int width, int height) override final;

	virtual void Special(int key, int x, int y) override final;

	virtual void OnKeyDown(unsigned char key, int x, int y) override final;

	virtual void OnMouseClick(int button, int state, int x, int y) override final;

	virtual void RefreshDisplay(int t) override final;

	virtual void Time(int t) override final;

private:
	Options& options;
};