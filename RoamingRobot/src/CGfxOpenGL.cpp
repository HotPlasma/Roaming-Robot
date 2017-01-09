#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "CGfxOpenGL.h"
#include "Robot.h"
#include "TextureLoader.h"
#include "ModelReader.h"
#include "Model.h"
#include "Scene.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{
	CameraPos = glm::vec3(1, 1, 1);
}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init()
{	
	theRobot = new Robot;
	theScene = new Scene("assets/scenes/Room.txt");

	_fRotationAngle = 0.0f;

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
	
	//Scene Room("assets/scenes/Room.txt");

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
	//CameraPos = glm::vec3(theRobot->ReturnRobotPosition().x, theRobot->ReturnRobotPosition().y + 5, theRobot->ReturnRobotPosition().z - 2);
	SetupProjection(1024, 768, true);
	//cout << CameraPos.x << " " << CameraPos.y << " " << CameraPos.z << endl;
}

void CGfxOpenGL::Render()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix (clear to default position and orientation)
	glLoadIdentity();

	// Draw Models
	for (int i = 0; i < theScene->ModelList.size(); i++)
	{
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1.f, 1.f, 1.f);
		//glTranslatef(0.0f, 0.0f, -30.0f);
		theScene->ModelList[i].DrawModel(false, true);
		glPopMatrix();
	}

	// Draw Robot
	glPushMatrix();							// put current matrix on stack
		glLoadIdentity();					// reset matrix
		glTranslatef(0.0f, 0.0f, -30.0f);	// move to (0, 0, -30)
		glRotatef(_fRotationAngle, 0.0f, 1.0f, 0.0f);	// rotate the robot on its y-axis
		theRobot->DrawRobot(0.0f, 0.0f, 0.0f);		// draw the robot
	glPopMatrix();




}
