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
#include <string>
#include "ModelReader.h"

using namespace std;

class Model
{
private:
	string sName; // A moniker for each model
	string sFileName; // File location of the obj
	string sTexture; // File location of the texture
	int ModelMaterial; // Which material the model with have. Different integers are different materials.

	glm::vec3 ModelPosition; // Position of Model
	glm::vec3 ModelRotation; // Rotation of Model
	glm::vec3 ModelScale; // Scale of Model

	bool m_bCollectable = false; // is the model a collectable?
	bool m_bCollected = false; // has the collectable been collected?

	GLuint m_textureID; // ID of the texture
	ModelReader* m_modelReader; // Model Reader for the render the model
public:
	Model(); // Constructor
	Model(string FileLocation, string TextureLocation, glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale, int MaterialID); // Full constructor
	string GetName(); // Returns moniker
	string GetFileLocation(); // Returns location of obj
	GLuint GetTextureLocation(); // Returns location of texture
	glm::vec3 GetPosition(); // Returns rosition of model
	glm::vec3 GetRotation(); // Returns rotation of model
	glm::vec3 GetScale(); // Returns scale of model
	bool CheckIfCollectable(); // Check if a model is a collectable
	bool GetCollected(); // Check if a collectable has been collected
	int GetMaterial(); // Returns materialID

	void SetCollectable();
	void SetCollected(bool Collected); // Set collected or not collected for a collectable
	void SetName(string newName);
	void SetTexture(GLuint TextureID); // Set texture ID
	void SetFileLocation(string NewLocation); // Set obj location
	void SetTextureLocation(string NewLocation); // Set texture location
	void SetPosition(glm::vec3 NewPosition); // Set model position
	void SetRotation(glm::vec3 NewRotation); // Set model rotation
	void SetScale(glm::vec3 NewScale); // Set model scale
	void SetMaterial(int MaterialID); // Set model MaterialID

	void LoadModel(string Model); // Loads in the model to be rendered
	void DrawModel(bool drawWithNormals, bool drawWithTexture); // Draws model


};

