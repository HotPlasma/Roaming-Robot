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
#include "Model.h"
#include <vector>
#include "TextureLoader.h"
#include <glm.hpp>
#include <tinyxml2.h>

class Scene
{
public:
	Scene(string filename); // Takes a file name and loads in a scene
	vector<Model> ModelList; // Vector of models which makes up the scene
private:
	vector<GLuint> m_textureID; // Vector of all the textures for models
	TextureLoader* tl; // Texture loader
	void ReadSceneFile(string filename); // Function to proccess textfile
};