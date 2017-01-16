#ifdef _WINDOWS
#include <windows.h>
#endif

#include "stdafx.h"

//#include <gl/gl.h>
//#include <gl/glu.h>
#include <math.h>
#include "CGfxOpenGL.h"
#include "Robot.h"
#include "TextureLoader.h"
#include "ModelReader.h"
#include "Model.h"
#include "Scene.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

GLfloat m_lightPosition[] = { -50.0f, +100.0f, +20.0f, 1.0f };

CGfxOpenGL::CGfxOpenGL()
{
	CameraPos = glm::vec3(1, 1, 1);
	CollectableSpeed = glm::vec3(0, 1, 0);

}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init()
{	
	//theRobot = new Robot;
	

	

	theRobot = new Robot;
	theScene = new Scene("assets/scenes/Room.cfg");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

bool CGfxOpenGL::Shutdown()
{
	delete theRobot;

	return true;
}

void CGfxOpenGL::ProcessInput(int input)
{
	switch (input)
	{
	case VK_UP:
		theRobot->MoveForward(0.5f);
		break;

	case VK_DOWN:
		theRobot->MoveForward(-0.5f);
		break;
	case VK_LEFT:
		theRobot->_fRotationAngle += 2.5f;
		break;
	case VK_RIGHT:
		theRobot->_fRotationAngle += -2.5f;
		break;
	}

	
}

void CGfxOpenGL::SetMaterialDefault()
{
	GLfloat materialWhiteAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat materialWhiteDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat materialWhiteSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// so keeps light colour
	GLfloat materialWhiteShininess = 700.0f;
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialWhiteAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialWhiteDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialWhiteSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialWhiteShininess);
}

void CGfxOpenGL::SetLightPosition(float x, float y, float z)
{
	m_lightPosition[0] = x;
	m_lightPosition[1] = y;
	m_lightPosition[2] = z;
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPosition);
}

void CGfxOpenGL::ConfigureLightSources()
{
	GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat noLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat lightModelAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0 };

	// put light behind and above us on left
	SetLightPosition(-40.0f, +20, -23.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
	glLightfv(GL_LIGHT0, GL_AMBIENT, noLight);			// no ambient light from the source

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);	// use global ambient instead

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// with lighting glColor no longer applies
	// create a default material for the models
	SetMaterialDefault();
}

int CGfxOpenGL::ReturnCollectableCount()
{
	return iBatteriesCollected;
}

Robot* CGfxOpenGL::ReturnRobot()
{
	return theRobot;
}
void CGfxOpenGL::ChangeCamera(glm::vec3 CameraPosition)
{
	CameraPos = glm::vec3(CameraPosition.x, CameraPosition.y, CameraPosition.z);
}

void CGfxOpenGL::SetupProjection(int width, int height, bool RobotReady)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;					
	}

	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
	
	if (RobotReady)
	{
		gluLookAt(CameraPos.x, CameraPos.y, CameraPos.z, theRobot->ReturnRobotPosition().x, theRobot->ReturnRobotPosition().y , theRobot->ReturnRobotPosition().z, 0, 1, 0);
	}
	else
	{
		gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	}
	

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;

}

void CGfxOpenGL::Prepare(float dt)
{
	//_fRotationAngle += 45.0f * dt;					// increase our rotation angle counter
	//if (_fRotationAngle >= 360.0f)					// if we've gone in a circle, reset counter
	//	_fRotationAngle = 0.0f;

	theRobot->Prepare(dt);

	SetLightPosition(-40 , 25 , 23);
	//CameraPos = glm::vec3(theRobot->ReturnRobotPosition().x, theRobot->ReturnRobotPosition().y + 5, theRobot->ReturnRobotPosition().z - 2);
	SetupProjection(1024, 768, true);
	for (int i = 0; i < theScene->ModelList.size(); i++)
	{
		if (theScene->ModelList.at(i).CheckIfCollectable())
		{
			if (!theScene->ModelList.at(i).GetCollected())
			{
				if (theScene->ModelList.at(i).GetPosition().y > -7)
				{
					CollectableSpeed = glm::vec3(0, -0.03, 0);
				}
				else if (theScene->ModelList.at(i).GetPosition().y < -10)
				{
					CollectableSpeed = glm::vec3(0, 0.03, 0);
				}
				theScene->ModelList.at(i).SetPosition(theScene->ModelList.at(i).GetPosition() + CollectableSpeed);
				theScene->ModelList.at(i).SetRotation(glm::vec3(45, theScene->ModelList.at(i).GetRotation().y + 1, theScene->ModelList.at(i).GetRotation().z));

				glm::vec3 Distance = theRobot->ReturnRobotPosition() - theScene->ModelList.at(i).GetPosition();

				if (sqrtf(powf(Distance.x, 2.0f) + powf(Distance.z, 2.0f)) < 5)
				{
					theScene->ModelList.at(i).SetCollected();
					iBatteriesCollected++;
				}
			}
		}
	}
	//cout << CameraPos.x << " " << CameraPos.y << " " << CameraPos.z << endl;
}

void CGfxOpenGL::Render()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix (clear to default position and orientation)
	glLoadIdentity();


	ConfigureLightSources();


	// Draw Models
	for (int i = 0; i < theScene->ModelList.size(); i++)
	{
		if (!theScene->ModelList.at(i).GetCollected())
		{
			glPushMatrix();
			glLoadIdentity();
			//glColor3f(1.f, 1.f, 1.f);
			theScene->ModelList[i].DrawModel(true, true);
			glPopMatrix();
		}
	}

	// Draw Robot
	glPushMatrix();							// put current matrix on stack
		glLoadIdentity();					// reset matrix
		glTranslatef(0.0f, 0.0f, 0.0f);	// move to (0, 0, 0)
		glRotatef(_fRotationAngle, 0.0f, 1.0f, 0.0f);	// rotate the robot on its y-axis
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_CULL_FACE);
		theRobot->DrawRobot(0.0f, 0.0f, 0.0f);		// draw the robot
		glEnable(GL_CULL_FACE);
		glCullFace(GL_COLOR_MATERIAL);
		glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();




}
