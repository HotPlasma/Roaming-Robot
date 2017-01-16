#include "HUD.h"

HUD::HUD(int WindowWidth, int WindowHeight)
{

//	ToastTimer.restart();
	ToastVisible = false;

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

	ToastText.setFont(SpaceFont);
	ToastText.setCharacterSize(30);
	ToastText.setString("Battery Collected");

	sf::FloatRect ToastRect = ToastText.getLocalBounds();
	ToastText.setOrigin(ToastRect.left + ToastRect.width / 2.0f, ToastRect.top + ToastRect.height / 2.0f);
	
	ToastText.setPosition(sf::Vector2f(WindowWidth / 2 , WindowHeight / 2 - 60));

	BatteryCount.setFont(SpaceFont);
	BatteryCount.setString("0");
	BatteryCount.setCharacterSize(25);

	// Centre Text
	sf::FloatRect CountRect = BatteryCount.getLocalBounds();
	BatteryCount.setOrigin(CountRect.left + CountRect.width / 2.0f, CountRect.top + CountRect.height / 2.0f);
	BatteryCount.setPosition(sf::Vector2f(WindowWidth / 4.0f - 60, WindowHeight / 8.0f));

}

void::HUD::SendToastToScreen(string ToastMessage)
{
	ToastTimer.restart();
	ToastText.setString(ToastMessage);
	if (ToastTimer.getElapsedTime().asSeconds() < 3) // = true
	{
		ToastVisible = true;
	}
	
	
	
		
}

void HUD::draw(RenderTarget & target, RenderStates states) const
{
	if (ToastTimer.getElapsedTime().asSeconds() < 3 && ToastVisible == true) // = true
	{
		target.draw(ToastText);
	}

	target.draw(m_Battery);
	target.draw(BatteryCount);
}

void HUD::UpdateCollectableCount(unsigned int CollectableCount)
{
	BatteryCount.setString(to_string(CollectableCount));
}

