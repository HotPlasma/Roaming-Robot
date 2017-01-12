#pragma once

#include "stdafx.h"
#include <string>
#include "ModelReader.h"

using namespace std;

class Model
{
private:
	string sFileName; // File location of the obj
	string sTexture; // File location of the texture
	int ModelMaterial; // Which material the model with have. Different integers are different materials.

	glm::vec3 ModelPosition; // Position of Model
	glm::vec3 ModelRotation; // Rotation of Model
	glm::vec3 ModelScale; // Scale of Model

	bool m_bCollectable = false;
	bool m_bCollected = false;

	GLuint m_textureID; // ID of the texture
	ModelReader* m_modelReader; // Model Reader for the render the model
public:
	Model(); // Constructor
	Model(string FileLocation, string TextureLocation, glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale, int MaterialID); // Full constructor
	string GetFileLocation(); // Returns location of obj
	GLuint GetTextureLocation(); // Returns location of texture
	glm::vec3 GetPosition(); // Returns rosition of model
	glm::vec3 GetRotation(); // Returns rotation of model
	glm::vec3 GetScale(); // Returns scale of model
	bool CheckIfCollectable();
	bool GetCollected();
	int GetMaterial(); // Returns materialID

	void SetCollectable();
	void SetCollected();
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

