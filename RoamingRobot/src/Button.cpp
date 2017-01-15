#include <Button.h>
#include <vector>

Button::Button()
{
	
}

Button::Button(float fX, float fY, int iTextureID, TextureVault* texLoader2)
{
	SetProperties(fX, fY, iTextureID, texLoader2);
}

void Button::SetProperties(float fX, float fY, int iTextureID, TextureVault* texLoader2)
{
	m_TexLoader = texLoader2;
	m_Sprite.setPosition(fX, fY);
	m_Sprite.setTexture(*m_TexLoader->getTextureIterator(iTextureID));
	m_iCurrentTexID = iTextureID;
	m_bActive = false;
}

void Button::ChangeTexture(int iNewTextureID)
{
	m_Sprite.setTexture(*m_TexLoader->getTextureIterator(iNewTextureID));
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void Button::CheckHover(sf::Vector2f MousePos)
{
	// Mouse is pointing at button
	if (MousePos.x > m_Sprite.getPosition().x && MousePos.x < m_Sprite.getPosition().x + m_Sprite.getGlobalBounds().width &&
		MousePos.y > m_Sprite.getPosition().y && MousePos.y < m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height)
	{
			ChangeTexture(m_iCurrentTexID + 1); // Change texture to highlighted texture
			m_bActive = true; 
	}
	// Mouse is not pointing at button
	else
	{
		ChangeTexture(m_iCurrentTexID); 
		m_bActive = false;
	}

}

bool Button::isActive()
{
	return m_bActive;
}

Button::~Button()
{
	m_TexLoader = NULL;
}