
#include <stdafx.h>

#include "Robot.h"
#include <Game.h>
#include <MainMenu.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <HUD.h>
#include <EndScreen.h>


// Enums for managing menu choices and selections
enum MenuSelection
{
	CLOSE_GAME,START_GAME
};
// Enum for states of the game
enum State
{
	MENU,GAME,END_SCREEN
};

// Window/View Variables
int iWindowWidth = 1024;
int iWindowHeight = 768;
int iWindowBits = 32;

// OpenGL/View Variables
unsigned int ui_CameraID = 1;
int iDepthBits = 24;
int iStencilBits = 8;
int iAntiAliasingLevel = 2;
// OpenGL versions
int majorVersion = 3;
int minorVersion = 3;

// Seperate Classes
Game *g_Game = NULL;
Menu g_SelectionMenu(iWindowWidth,iWindowHeight);
HUD g_HeadsUpDisplay(iWindowWidth, iWindowHeight);
EndScreen g_EndScreen(iWindowWidth, iWindowHeight);

// Timer
sf::Clock g_TimerClock;





int main()
{
	// Create Window
	sf::ContextSettings context(iDepthBits, iStencilBits, iAntiAliasingLevel, majorVersion, minorVersion);
	sf::RenderWindow window(sf::VideoMode(iWindowWidth, iWindowHeight, iWindowBits), "Roaming Robot", 7U, context);

	// Initation OpenGL Games Properties.
	g_Game = new Game;
	// Load in required assets
	g_Game->Init();

	int iState = MENU;

	unsigned int u_iCollectableCounter = 0; // Reset counter


	while (window.isOpen()) // Window is open loop
	{
		sf::Event event;

		// React accordingly based on which button clicked
		if (g_TimerClock.getElapsedTime().asSeconds() > 0.005)
		{
			switch (g_SelectionMenu.update(g_TimerClock.getElapsedTime().asSeconds()))
			{
			case START_GAME:
				iState = GAME;
				g_Game->ReturnRobot()->ResetRotations();
				g_SelectionMenu.ResetClick();
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
					g_SelectionMenu.TakeMousePos(window.mapPixelToCoords(Mouse::getPosition(window)));
				}
				// If mouse clicked, check if button clicked on menu
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						g_SelectionMenu.Click();
					}
				}

			}
			// Events exclusive for game state
			else if (iState == GAME)
			{
				// Resizes/adjusts viewport when window resized for opengl 
				if (event.type == sf::Event::Resized)
				{
					g_Game->SetupProjection(iWindowWidth, iWindowHeight, false);

				}
				// Left button cycles cameras up
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) 
				{
					if (ui_CameraID == 3)
					{
						ui_CameraID = 1;
					}
					else
					{
						ui_CameraID++;
					}
				}
				// Left button cycles cameras down
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Right))
				{
					if (ui_CameraID == 1)
					{
						ui_CameraID = 3;
					}
					else
					{
						ui_CameraID--;
					}
				}

				// Stop robot from moving legs when the player stops moving

				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Up || event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::W))
				{
					g_Game->ReturnRobot()->ToggleAllMovement();
					g_Game->ReturnRobot()->Moving = false;
				}
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Down || event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::S))
				{
					g_Game->ReturnRobot()->ToggleAllMovement();
					g_Game->ReturnRobot()->Moving = false;
				}

				// Process movement controls
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						PostQuitMessage(0);
					}
					if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
					{
						g_Game->ReturnRobot()->ToggleAllMovement();
						g_Game->ProcessInput(VK_UP);
					}

					if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
					{
						g_Game->ReturnRobot()->ToggleAllMovement();
						g_Game->ProcessInput(VK_DOWN);

					}

					if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
					{
						g_Game->ProcessInput(VK_LEFT);
					}

					if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
					{
						g_Game->ProcessInput(VK_RIGHT);
					}
				}
					
				}
				// EndScreen events
				else if (iState == END_SCREEN)
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Return)
						{
							// Return to menu if return pressed on the end screen
							iState = MENU;
						}
					}
				}
				
			}
			// Draw Menu Objects
			if (iState == MENU)
			{
				window.pushGLStates();
				window.draw(g_SelectionMenu);
				window.popGLStates();
			}
			// Update cameras while in game state
			if (iState == GAME)
			{
				if (g_TimerClock.getElapsedTime().asSeconds() > 0.005) // Check every 0.005 seconds
				{
					//Assign camera position to each value
					if (ui_CameraID == 1)
					{
						g_Game->ChangeCamera(glm::vec3(-100, 30, 30));
					}
					else if (ui_CameraID == 2)
					{
						g_Game->ChangeCamera(glm::vec3(1, 30, 100));
					}

					else if (ui_CameraID == 3)
					{
						g_Game->ChangeCamera(glm::vec3(100, 30, -30));
					}
					// Draw game objects
					g_Game->Prepare(g_TimerClock.getElapsedTime().asSeconds());
					g_Game->Render();
					window.pushGLStates();
					
					// Heads Up Display (HUD)
					if (g_Game->ReturnCollectableCount() > u_iCollectableCounter)
					{
						g_HeadsUpDisplay.UpdateCollectableCount(g_Game->ReturnCollectableCount()); // Update collectable count
						g_HeadsUpDisplay.SendToastToScreen("Battery Collected"); // Send battery collected toast to user
						u_iCollectableCounter++; // Increment battery count
						
					}
					window.draw(g_HeadsUpDisplay); // Draw HUD
					window.popGLStates();
					g_TimerClock.restart(); // Restart Timer
					
				}
			}

			// If player collects 3 collectables end level
			if (g_Game->ReturnCollectableCount() >= 3)
			{
				//g_Game->ReturnRobot()->ToggleAllMovement();
				iState = END_SCREEN; // Switch screen
				g_Game->ResetCollectableCount(); // Reset collectable conter
				g_HeadsUpDisplay.UpdateCollectableCount(g_Game->ReturnCollectableCount()); // Update HUD
				u_iCollectableCounter = 0; // Reset local collectable count
				g_Game->ResetCollected(); // Reset foreign collectable count
				g_Game->ReturnRobot()->SetRobotPosition(glm::vec3(0, 0, 0)); // Reset Robots position to starting pos
				
			}

			if (iState == END_SCREEN) // Draw End Screen content
			{
				window.pushGLStates();
				window.draw(g_EndScreen);
				window.popGLStates();
			}
			// Draw window
			window.display();

	}
}
