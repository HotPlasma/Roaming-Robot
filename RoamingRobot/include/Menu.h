#pragma once

#include <iostream>
#include <stdafx.h>
#include <TextureVault.h>
#include <Button.h>

class AbstractMenu : public sf::Drawable
{
private:
	bool m_bClicked; // True if button has been clicked


public:
	AbstractMenu();
	AbstractMenu(int WindowWidth, int WindowHeight); // Constructor					
	sf::Sprite m_Background;
	// Font for a screen
	Font m_Font;

	TextureVault m_TexLoader; // Holds textures for buttons

	Vector2f m_MousePos; // Holds mouse position
	virtual void TakeMousePos(Vector2f Pos) {}; // Returns mouse pos 
	virtual void draw(RenderTarget &target, RenderStates states) const {};
	virtual int update(float fTimestep) { return 1; };
	void Click();
	void ResetClick();
};