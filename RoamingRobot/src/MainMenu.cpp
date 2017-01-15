#include <MainMenu.h>
#include <Button.h>

Menu::Menu(int WindowWidth, int WindowHeight)
{
	// Load in all textures needed for main menu
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"MenuBackground.png",
		"NewGame.png",
		"NewGameHover.png",
		"Exit.png",
		"ExitHover.png",
			"Arrows.png",
			"Mouse.png"
	});

	// Set up main menu background
	m_Background.setPosition(0, 0);
	m_Background.setTexture(*m_TexLoader.getTextureIterator(0));

	m_Arrows.setPosition(50, 200);
	m_Arrows.setTexture(*m_TexLoader.getTextureIterator(5));

	m_Mouse.setPosition(700, 200);
	m_Mouse.setTexture(*m_TexLoader.getTextureIterator(6));


	// Sets up font for heads up display
	if (!SpaceFont.loadFromFile("assets\\Fonts\\spaceage.TTF"))
	{
		cout << "Error, Space Age font failed to load";
	}

	// Sets up game title on main menu

	m_Title.setFont(SpaceFont);
	m_Title.setString("Roaming Robot");
	m_Title.setCharacterSize(80);

	// Centre Text
	sf::FloatRect TitleRect = m_Title.getLocalBounds();
	m_Title.setOrigin(TitleRect.left + TitleRect.width / 2.0f, TitleRect.top + TitleRect.height / 2.0f);
	m_Title.setPosition(sf::Vector2f(WindowWidth / 2.0f, WindowHeight / 8.0f));

	//m_Title.setPosition(200, 40);
	//m_Title.setColor(sf::Color::White);

	// Sets up main menu buttons positions and starting textures
	m_NewGameButton.SetProperties(WindowWidth / 2 - 100, 200, 1, &m_TexLoader);

	m_ExitButton.SetProperties(WindowWidth / 2 - 100, 600, 3, &m_TexLoader);

	m_bClicked = false;
}

void Menu::TakeMousePos(sf::Vector2f Pos)
{
	// Changes buttons sprites if hovered over
	m_NewGameButton.CheckHover(Pos);
	m_ExitButton.CheckHover(Pos);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_Background);
	target.draw(m_Title);
	target.draw(m_NewGameButton);
	target.draw(m_ExitButton);
	target.draw(m_Arrows);
	target.draw(m_Mouse);
}

int Menu::update(float fTimestep)
{
	// Returns value dependent on which button was clicked
	if (m_bClicked)
	{
		if (m_NewGameButton.isActive())
		{
			return 2;
		}
		else if (m_ExitButton.isActive())
		{
			return 1;
		}
		m_bClicked = false;
	}
	return 0;
}

void Menu::Click()
{
	m_bClicked = true;
};
