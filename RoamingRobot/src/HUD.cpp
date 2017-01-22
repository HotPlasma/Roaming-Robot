#include "HUD.h"

HUD::HUD(int WindowWidth, int WindowHeight)
{
	m_bToastVisible = false; // Hide message shown to player

	m_TexLoader.setBaseDirectory("assets\\UI\\"); // Load in files
	m_TexLoader.load(std::vector<std::string>{
		"Battery.png"
	});

	m_Battery.setPosition(WindowWidth / 4 - 200 , 20);
	m_Battery.setTexture(*m_TexLoader.getTextureIterator(0)); // Assign texture

	//Load in font
	if (!m_SpaceFont.loadFromFile("assets\\Fonts\\spaceage.TTF"))
	{
		cout << "Error, Space Age font failed to load";
	}

	m_ToastText.setFont(m_SpaceFont);
	m_ToastText.setCharacterSize(30);
	m_ToastText.setString("Battery Collected");

	sf::FloatRect ToastRect = m_ToastText.getLocalBounds();
	m_ToastText.setOrigin(ToastRect.left + ToastRect.width / 2.0f, ToastRect.top + ToastRect.height / 2.0f); // Center correctly
	
	m_ToastText.setPosition(sf::Vector2f(WindowWidth / 2 , WindowHeight / 2 - 60));

	m_BatteryCount.setFont(m_SpaceFont);
	m_BatteryCount.setString("0");
	m_BatteryCount.setCharacterSize(25);

	// Centre Text
	sf::FloatRect CountRect = m_BatteryCount.getLocalBounds();
	m_BatteryCount.setOrigin(CountRect.left + CountRect.width / 2.0f, CountRect.top + CountRect.height / 2.0f); // Center correctly
	m_BatteryCount.setPosition(sf::Vector2f(WindowWidth / 4.0f - 60, WindowHeight / 8.0f)); 

}

void::HUD::SendToastToScreen(string ToastMessage)
{
	// Show passed message for 3 seconds then hide it
	m_ToastTimer.restart();
	m_ToastText.setString(ToastMessage);
	if (m_ToastTimer.getElapsedTime().asSeconds() < 3) // Show message for 3 seconds
	{
		m_bToastVisible = true;
	}
	
	
	
		
}

void HUD::draw(RenderTarget & target, RenderStates states) const
{
	if (m_ToastTimer.getElapsedTime().asSeconds() < 3 && m_bToastVisible == true) // Draw toast for 3 seconds
	{
		target.draw(m_ToastText);
	}

	target.draw(m_Battery);
	target.draw(m_BatteryCount);
}

void HUD::UpdateCollectableCount(unsigned int CollectableCount)
{
	m_BatteryCount.setString(to_string(CollectableCount));
}

