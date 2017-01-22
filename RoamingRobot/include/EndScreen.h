////////////////////////////////////////////////////////////
//
// Roaming Robot - Created by Jegor Kharlamov
// Created for Games Programming Year 3 Coursework at DMU - Games Programming Course
//
// This project is a collectathon made with personally developed game engine components
//
////////////////////////////////////////////////////////////
#pragma once

#include <Menu.h>

class EndScreen : public AbstractMenu
{

public:
	EndScreen(int WindowWidth, int WindowHeight); // Constructor
	void draw(RenderTarget &target, RenderStates states) const;
};