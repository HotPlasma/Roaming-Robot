
#include <stdafx.h>

#include "Robot.h"
#include "timer.h"
#include <MainMenu.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <HUD.h>

//Menu variables
#define CLOSE_GAME 1
#define START_GAME 2

//State variables
#define MENU 0
#define GAME 1

long windowWidth = 1024;
long windowHeight = 768;
unsigned int CameraID = 1;
long windowBits = 32;
bool fullscreen = false;
bool walking = false;

int depthBits = 24;
int stencilBits = 8;
int antiAliasingLevel = 2;
int majorVersion = 3;
int minorVersion = 3;

CGfxOpenGL *g_glRender = NULL;
Menu SelectionMenu(windowWidth,windowHeight);
HUD HeadsUpDisplay(windowWidth, windowHeight);
sf::Clock timerClock;

int iState = MENU;

int main()
{
	sf::ContextSettings context(depthBits, stencilBits, antiAliasingLevel, majorVersion, minorVersion);
	//	//sf::Window window(sf::VideoMode(windowWidth, windowHeight, 32), "Roaming Robot", 7U, context);
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "Roaming Robot", 7U, context);
	//sf::RenderWindow MenuWindow(sf::VideoMode(windowWidth, windowHeight), "Roaming Robot");

	//window.draw(SelectionMenu);
	//window.display();

	g_glRender = new CGfxOpenGL;
	g_glRender->Init();



	while (window.isOpen())
	{
		sf::Event event;

		if (timerClock.getElapsedTime().asSeconds() > 0.005)
		{
			switch (SelectionMenu.update(timerClock.getElapsedTime().asSeconds()))
			{
			case START_GAME:
				iState = GAME;
				break;

			case CLOSE_GAME:
				window.close();
				break;
			}
		}


		while (window.pollEvent(event))
		{
			// Neutral Events (Effect All Windows)
			// Close window if 'X' is clicked
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// Close window if escape key pressed
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}

			// If current state is in menu
			if (iState == MENU)
			{	
				// Take mouse coords reletive to window
				if (event.type == sf::Event::MouseMoved)
				{
					SelectionMenu.TakeMousePos(window.mapPixelToCoords(Mouse::getPosition(window)));
				}
				// If mouse clicked, check if button clicked on menu
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						SelectionMenu.Click();
					}
				}
				// Draw/Display menu
				
				//window.display();

			}
			else if (iState == GAME)
			{
			
				// Resize event : adjust viewport
				if (event.type == sf::Event::Resized)
				{
					g_glRender->SetupProjection(windowWidth, windowHeight, false);

				}

				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left))
				{
					if (CameraID == 3)
					{
						CameraID = 1;
					}
					else
					{
						CameraID++;
					}
				}
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Right))
				{
					if (CameraID == 1)
					{
						CameraID = 3;
					}
					else
					{
						CameraID--;
					}
				}
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Up))
				{
					g_glRender->ReturnRobot()->ToggleAllMovement();
					g_glRender->ReturnRobot()->Moving = false;
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						PostQuitMessage(0);
					}
					if (event.key.code == sf::Keyboard::Up)
					{
						g_glRender->ProcessInput(VK_UP);
					}

					if (event.key.code == sf::Keyboard::Down)
					{
						g_glRender->ProcessInput(VK_DOWN);
					}

					if (event.key.code == sf::Keyboard::Left)
					{
						g_glRender->ProcessInput(VK_LEFT);
					}

					if (event.key.code == sf::Keyboard::Right)
					{
						g_glRender->ProcessInput(VK_RIGHT);
					}
				}
					
				}
				
			}

			if (iState == MENU)
			{
				window.pushGLStates();
				window.draw(SelectionMenu);
				window.popGLStates();
			}
			if (iState == GAME)
			{
				if (timerClock.getElapsedTime().asSeconds() > 0.005)
				{
					if (CameraID == 1)
					{
						g_glRender->ChangeCamera(glm::vec3(-100, 30, 30));
					}
					else if (CameraID == 2)
					{
						g_glRender->ChangeCamera(glm::vec3(1, 30, 100));
					}

					else if (CameraID == 3)
					{
						g_glRender->ChangeCamera(glm::vec3(100, 30, -30));
					}
					//g_glRender->SetupProjection(windowWidth, windowHeight, false);
					g_glRender->Prepare(timerClock.getElapsedTime().asSeconds());
					g_glRender->Render();
					window.pushGLStates();
					// Heads Up Display
					HeadsUpDisplay.UpdateCollectableCount(g_glRender->ReturnCollectableCount());
					window.draw(HeadsUpDisplay);
					window.popGLStates();
					timerClock.restart();
				}
			}

			window.display();

	}
}
