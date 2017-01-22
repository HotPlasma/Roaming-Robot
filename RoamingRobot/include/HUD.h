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
	Font m_SpaceFont;

	// Title text
	Text m_BatteryCount;
	Text m_ToastText;
	
	bool m_bToastVisible;

	TextureVault m_TexLoader; // Holds textures for buttons

	sf::Clock m_ToastTimer; // Keeps track of how long a message stays on screen

public:
	HUD(int WindowWidth, int WindowHeight); // Constructor
	void draw(RenderTarget &target, RenderStates states) const;
	void UpdateCollectableCount(unsigned int CollectableCount);
	void SendToastToScreen(string ToastMessage);
};