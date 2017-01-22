////////////////////////////////////////////////////////////
//
// Roaming Robot - Created by Jegor Kharlamov
// Created for Games Programming Year 3 Coursework at DMU - Games Programming Course
//
// This project is a collectathon made with personally developed game engine components
//
////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

using namespace std;

class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);



	int LoadBMP(string location, GLuint &texture, bool repeatTexture);
};

