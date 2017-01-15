#include "HUD.h"

HUD::HUD(int WindowWidth, int WindowHeight)
{
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"Battery.png"
	});

	m_Battery.setPosition(WindowWidth / 4 - 200 , 20);
	m_Battery.setTexture(*m_TexLoader.getTextureIterator(0));

	if (!SpaceFont.loadFromFile("assets\\Fonts\\spaceage.TTF"))
	{
		cout << "Error, Space Age font failed to load";
	}

	BatteryCount.setFont(SpaceFont);
	BatteryCount.setString("0");
	BatteryCount.setCharacterSize(25);

	// Centre Text
	sf::FloatRect TitleRect = BatteryCount.getLocalBounds();
	BatteryCount.setOrigin(TitleRect.left + TitleRect.width / 2.0f, TitleRect.top + TitleRect.height / 2.0f);
	BatteryCount.setPosition(sf::Vector2f(WindowWidth / 4.0f - 60, WindowHeight / 8.0f));

}

void HUD::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_Battery);
	target.draw(BatteryCount);
}

void HUD::UpdateCollectableCount(unsigned int CollectableCount)
{
	BatteryCount.setString(to_string(CollectableCount));
}

