#pragma once

#include <Menu.h>

class Menu : public AbstractMenu
{
	private:
		// Buttons on menu screen
		sf::Sprite m_Arrows;
		sf::Sprite m_Mouse;
		Button m_NewGameButton;
		Button m_ExitButton;

		// Font for menu screen
	
		// Title text
		Text m_Title;

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