#pragma once

#include <Menu.h>

class EndScreen : public AbstractMenu
{

public:
	EndScreen(int WindowWidth, int WindowHeight); // Constructor
	void draw(RenderTarget &target, RenderStates states) const;
};