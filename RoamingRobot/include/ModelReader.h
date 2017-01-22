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

class ModelReader
{
	private:
		
		static const int forwardSlash = 0x2F; // Forward slash

		// Store data from the OBJ files

		vector<float> m_vertices;					
		vector<float> m_vertexNormals;				
		vector<float> m_vertexTextureCoordinates;	

		vector<unsigned int> m_faceVertexIndices;
		vector<unsigned int> m_faceTextureIndices;
		vector<unsigned int> m_faceNormalIndices;

		string m_modelName; // Name of the model

		vector<float> m_vertexTriplets;	
		vector<float> m_vertexNormalTriplets; 
		vector<float> m_vertexTexturePairs;

	public:
		ModelReader(string filename);
		~ModelReader(void);

		void ModelReader::ReadModelObjData(string filename);

		void ProcessVertexLine(istringstream& iss);
		void ProcessVertexNormalLine(istringstream& iss);
		void ProcessVertexTextureLine(istringstream& iss);
		void ProcessFaceLine(istringstream& iss);


		void CreateExpandedVertices();
		void CreateExpandedNormals();
		void CreateExpandedTextureCoordinates();

		vector<float>& GetVertices();
		vector<float>& GetNormals();
		vector<float>& GetTextureCoordinates();

};

