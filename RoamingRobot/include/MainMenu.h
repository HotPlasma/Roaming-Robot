#pragma once

#include <iostream>
#include <stdafx.h>
#include <TextureVault.h>
#include <Button.h>

class Menu : public sf::Drawable
{
	private:
		// Buttons on menu screen
		sf::Sprite m_Background;
		sf::Sprite m_Arrows;
		sf::Sprite m_Mouse;
		Button m_NewGameButton;
		Button m_ExitButton;

		// Font for menu screen
		Font m_SpaceFont;
	
		// Title text
		Text m_Title;

		TextureVault m_TexLoader; // Holds textures for buttons

		Vector2f m_MousePos; // Holds mouse position
		bool m_bClicked; // True if button has been clicked


public:
	Menu(int WindowWidth, int WindowHeight); // Constructor
	void TakeMousePos(Vector2f Pos); // Returns mouse pos 
	void draw(RenderTarget &target, RenderStates states) const;
	int update(float fTimestep);
	void Click();
	void ResetClick();
};