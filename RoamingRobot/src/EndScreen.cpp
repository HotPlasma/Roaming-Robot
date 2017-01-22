#include "..\include\EndScreen.h"

EndScreen::EndScreen(int WindowWidth, int WindowHeight)
{
	// Load in all textures needed for main menu
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"EndScreen.png"
	});

	// Set up main menu background
	m_Screen.setPosition(0, 0);
	m_Screen.setTexture(*m_TexLoader.getTextureIterator(0));
}

void EndScreen::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_Screen);
}
