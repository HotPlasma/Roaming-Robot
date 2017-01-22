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
#include <SFML/Graphics.hpp>
#include <TextureVault.h>

class Button : public sf::Drawable
{
private:
	sf::Sprite m_Sprite; // Buttons sprite
	int m_iCurrentTexID; // Assigned texture for button
	TextureVault* m_TexLoader;
	bool m_bActive; // Button is Active if being hovered over

public:
	Button(); // Default constructor 
	Button(float fX, float fY, int iTextureID, TextureVault* texLoader2); // Creates button with given parameters
	void SetProperties(float fX, float fY, int iTextureID, TextureVault* texLoader2);
	void ChangeTexture(int iNewTextureID); // Allows button texture to be changed
	void CheckHover(Vector2f MousePos); // Checks if mouse curser is hovering over button 
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool isActive(); // Checks if button is Active
	~Button(); 

};