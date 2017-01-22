#include <EndScreen.h>

EndScreen::EndScreen(int WindowWidth, int WindowHeight)
{
	// Load in all textures needed for menu
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"EndScreen.png"
	});

	// Set up background
	m_Background.setPosition(0, 0);
	m_Background.setTexture(*m_TexLoader.getTextureIterator(0));
}

void EndScreen::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_Background);
}
