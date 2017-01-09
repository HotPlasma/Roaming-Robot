#include "stdafx.h"
#include "Model.h"

Model::Model()
{

}

Model::Model(string FileLocation, string TextureLocation, glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale, int MaterialID)
{
	// Constucts a model with the given variables
	sFileName = FileLocation;
	sTexture = TextureLocation;
	ModelPosition = Position;
	ModelRotation = Rotation;
	ModelScale = Scale;
	ModelMaterial = MaterialID;
}

string Model::GetFileLocation()
{
	return sFileName;
}

GLuint Model::GetTextureLocation()
{
	return m_textureID;
}

glm::vec3 Model::GetPosition()
{
	return ModelPosition;
}

glm::vec3 Model::GetRotation()
{
	return ModelRotation;
}

glm::vec3 Model::GetScale()
{
	return ModelScale;
}

int Model::GetMaterial()
{
	return ModelMaterial;
}



void Model::SetFileLocation(string NewLocation)
{
	sFileName = NewLocation;
}

void  Model::SetTextureLocation(string NewLocation)
{
	sTexture = NewLocation;
}

void  Model::SetPosition(glm::vec3 NewPosition)
{
	ModelPosition = NewPosition;
}

void  Model::SetRotation(glm::vec3 NewRotation)
{
	ModelRotation = NewRotation;
}

void  Model::SetScale(glm::vec3 NewScale)
{
	ModelScale = NewScale;
}

void Model::SetTexture(GLuint TextureID)
{
	m_textureID = TextureID;
}

void Model::SetMaterial(int Material)
{
	ModelMaterial = Material;
}

void Model::LoadModel(string Model)
{
	m_modelReader = new ModelReader(Model);
}

void Model::DrawModel(bool drawWithNormals, bool drawWithTexture)
{

	// Translates model 
	glTranslatef(ModelPosition.x, ModelPosition.y, ModelPosition.z);

	// Performs rotation of model
	glRotatef(ModelRotation.x, 1, 0, 0);
	glRotatef(ModelRotation.y, 0, 1, 0);
	glRotatef(ModelRotation.z, 0, 0, 1);

	// Scales model if necessary 
	glScalef(ModelScale.x, ModelScale.y, ModelScale.z);
	




	// activate and specify pointer to vertex array

	glEnableClientState(GL_VERTEX_ARRAY);
	vector<float>& vertices = m_modelReader->GetVertices();
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);



	// pointer to normal array
	if (drawWithNormals)
	{
		glEnableClientState(GL_NORMAL_ARRAY);

		vector<float>&normals = m_modelReader->GetNormals();

		glNormalPointer(GL_FLOAT, 0, &normals[0]);
	}

	if (drawWithTexture)
	{
		glEnable(GL_TEXTURE_2D);
		vector<float>& textureCoordinates = m_modelReader->GetTextureCoordinates();
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, &textureCoordinates[0]);
	}


	// draw the shape...
	glDrawArrays(GL_TRIANGLES, 0, (unsigned int)vertices.size() / 3);
	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);

	if (drawWithNormals)
	{
		// deactivate
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	if (drawWithTexture)
	{
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
}