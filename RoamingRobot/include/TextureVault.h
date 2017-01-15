#pragma once

#include <vector>
#include <stdafx.h>
#include <iostream>

using namespace std;
using namespace sf;

class TextureVault
{
	private:
		vector<sf::Texture> m_Textures;// A vector of textures which all textures used in the program should be loaded into.
		string m_sBaseDirectory;// A string holding a base directory to find textures

	public:
		TextureVault(); // Initialises the Texture Loader
		void setBaseDirectory(string dir); // Allows the base directory which the textures are loaded from to be changed.
		void load(std::vector<string> fileNames); // Function where all necessary textures should be loaded in.
		std::vector<sf::Texture>::iterator getTextureIterator(const int &k_iIndex); // Allows textures from the Texture Loader to be used for sprite in other classes
};
