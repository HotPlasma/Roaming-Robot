#pragma once

#include <iostream>
#include <stdafx.h>
#include <TextureVault.h>

class EndScreen : public sf::Drawable
{
private:
	// Buttons on menu screen
	sf::Sprite m_Screen;

	TextureVault m_TexLoader; // Holds textures for buttons

public:
	EndScreen(int WindowWidth, int WindowHeight); // Constructor
	void draw(RenderTarget &target, RenderStates states) const;
};