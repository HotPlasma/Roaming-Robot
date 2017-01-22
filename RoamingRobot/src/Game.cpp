#ifdef _WINDOWS
#include <windows.h>
#endif

#include "stdafx.h"

#include <math.h>
#include "Game.h"
#include "Robot.h"
#include "TextureLoader.h"
#include "ModelReader.h"
#include "Model.h"
#include "Scene.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

GLfloat m_lightPosition[] = { -50.0f, +100.0f, +20.0f, 1.0f };

Game::Game()
{
	m_CameraPos = glm::vec3(1, 1, 1);
	m_CollectableSpeed = glm::vec3(0, 1, 0);

}

Game::~Game()
{
}

bool Game::Init()
{	
	m_theRobot = new Robot;
	m_theScene = new Scene("assets/scenes/Room.cfg"); // Load in scene file

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}


void Game::ProcessInput(int input)
{
	// Reacts depending on input given
	switch (input)
	{
	case VK_UP:
		m_theRobot->Move(0.5f);
		break;

	case VK_DOWN:
		m_theRobot->Move(-0.5f);
		break;
	case VK_LEFT:
		m_theRobot->m_fRotationAngle += 2.5f;
		break;
	case VK_RIGHT:
		m_theRobot->m_fRotationAngle += -2.5f;
		break;
	}

	
}

void Game::SetMaterialDefault() // Default material with realistic looking lighting
{
	GLfloat materialWhiteAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat materialWhiteDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat materialWhiteSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	
	GLfloat materialWhiteShininess = 700.0f; // Quite shiny specular lighting
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialWhiteAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialWhiteDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialWhiteSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialWhiteShininess);
}

void Game::SetLightPosition(float x, float y, float z)
{
	m_lightPosition[0] = x;
	m_lightPosition[1] = y;
	m_lightPosition[2] = z;
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPosition);
}

void Game::ConfigureLightSources()
{
	GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat noLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat lightModelAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0 };

	// Put light behind and above us on left
	SetLightPosition(-40.0f, +20, -23.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
	glLightfv(GL_LIGHT0, GL_AMBIENT, noLight);			// No ambient light from the source

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);	// Use global ambient instead

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	SetMaterialDefault();
}

int Game::ReturnCollectableCount()
{
	return m_uiBatteriesCollected;
}

void Game::ResetCollectableCount()
{
	m_uiBatteriesCollected = 0;
}

Robot* Game::ReturnRobot()
{
	return m_theRobot;
}
void Game::ChangeCamera(glm::vec3 CameraPosition)
{
	m_CameraPos = glm::vec3(CameraPosition.x, CameraPosition.y, CameraPosition.z);
}

void Game::SetupProjection(int width, int height, bool RobotReady)
{
	if (height == 0)					// Avoid Division by zero
	{
		height = 1;					
	}



	glViewport(0, 0, width, height);		// Reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// Set projection matrix current matrix
	glLoadIdentity();						// Reset projection matrix

	// Calculate aspect ratio of window
	gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
	
	// If robot already loaded in camera's view will follow him else look at static location
	if (RobotReady)
	{
		gluLookAt(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z, m_theRobot->ReturnRobotPosition().x, m_theRobot->ReturnRobotPosition().y , m_theRobot->ReturnRobotPosition().z, 0, 1, 0);
	}
	else
	{
		gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	}
	

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_iWindowWidth = width;
	m_iWindowHeight = height;

}

void Game::Prepare(float dt)
{
	// Set up robot
	m_theRobot->Prepare(dt);
	// Create light positionms
	SetLightPosition(-40 , 25 , 23);
	
	// Ensure cameras view follows robot
	SetupProjection(1024, 768, true);

	// for all models in scene
	for (int i = 0; i < m_theScene->ModelList.size(); i++)
	{
		if (m_theScene->ModelList.at(i).CheckIfCollectable()) // check if collectable
		{
			if (!m_theScene->ModelList.at(i).GetCollected()) // if collectable then slowly rotate and bob up and down
			{
				if (m_theScene->ModelList.at(i).GetPosition().y > -7)
				{
					m_CollectableSpeed = glm::vec3(0, -0.03, 0);
				}
				else if (m_theScene->ModelList.at(i).GetPosition().y < -10)
				{
					m_CollectableSpeed = glm::vec3(0, 0.03, 0);
				}
				m_theScene->ModelList.at(i).SetPosition(m_theScene->ModelList.at(i).GetPosition() + m_CollectableSpeed);
				m_theScene->ModelList.at(i).SetRotation(glm::vec3(45, m_theScene->ModelList.at(i).GetRotation().y + 1, m_theScene->ModelList.at(i).GetRotation().z));

				glm::vec3 Distance = m_theRobot->ReturnRobotPosition() - m_theScene->ModelList.at(i).GetPosition(); // Work out distance between robot and a collectable

				if (sqrtf(powf(Distance.x, 2.0f) + powf(Distance.z, 2.0f)) < 5) // If robot collides with a collectable mark it as collected and stop drawing it
				{
					m_theScene->ModelList.at(i).SetCollected(true);
					m_uiBatteriesCollected++;
				}
			}
		}
	}
}

void Game::ResetCollected()// Reset which collectables have been collected
{
	for (int i = 0; i < m_theScene->ModelList.size(); i++)
	{
		m_theScene->ModelList.at(i).SetCollected(false);
	}
}

void Game::Render()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix (clear to default position and orientation)
	glLoadIdentity();


	ConfigureLightSources();


	// Draw Models
	for (int i = 0; i < m_theScene->ModelList.size(); i++)
	{
		if (!m_theScene->ModelList.at(i).GetCollected()) // Draw all items except collected collectables
		{
			glPushMatrix();
			glLoadIdentity();
			m_theScene->ModelList[i].DrawModel(true, true);
			glPopMatrix();
		}
	}

	// Draw Robot
	glPushMatrix();							// put current matrix on stack
		glLoadIdentity();					// reset matrix
		glTranslatef(0.0f, 0.0f, 0.0f);	// move to (0, 0, 0)
		glRotatef(m_fRotationAngle, 0.0f, 1.0f, 0.0f);	// rotate the robot on its y-axis
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_CULL_FACE);
		m_theRobot->DrawRobot(0.0f, 0.0f, 0.0f);		// draw the robot
		glEnable(GL_CULL_FACE);
		glCullFace(GL_COLOR_MATERIAL);
		glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();




}
