////////////////////////////////////////////////////////////
//
// Roaming Robot - Created by Jegor Kharlamov
// Created for Games Programming Year 3 Coursework at DMU - Games Programming Course
//
// This project is a collectathon made with personally developed game engine components
//
////////////////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <stdafx.h>
#include <TextureVault.h>

class HUD : public sf::Drawable
{
private:
	// Battery icon
	sf::Sprite m_Battery;

	// Font
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