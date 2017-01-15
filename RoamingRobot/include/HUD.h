#pragma once

#pragma once

#include <iostream>
#include <stdafx.h>
#include <TextureVault.h>

class HUD : public sf::Drawable
{
private:
	// Buttons on menu screen
	sf::Sprite m_Battery;

	// Font for menu screen
	Font SpaceFont;

	// Title text
	Text BatteryCount;
	Text SplashText;

	TextureVault m_TexLoader; // Holds textures for buttons


public:
	HUD(int WindowWidth, int WindowHeight); // Constructor
	void draw(RenderTarget &target, RenderStates states) const;
	void UpdateCollectableCount(unsigned int CollectableCount);
};