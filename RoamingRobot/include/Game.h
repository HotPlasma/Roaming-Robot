#ifndef __GL_COMPONENT
#define __GL_COMPONENT



#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

#include "../libraries/glm/glm/glm.hpp"

class Robot;

class Scene;

class Game
{
private:
	float m_fRotationAngle; // Rotation of the robot

	glm::vec3 m_CameraPos; // Cameras Position

	int m_iWindowWidth; // Window width
	int m_iWindowHeight; // Window height


	glm::vec3 m_CollectableSpeed; // Speed at which a collectable bounces

	unsigned int m_uiBatteriesCollected = 0; // Batteries that have been collected

	// Instances of the robot and the scene
	Robot *m_theRobot;
	Scene *m_theScene;

public:
	Game();
	virtual ~Game();

	
	bool Init(); // Creates Essentals and returns true if successful
	Robot* ReturnRobot(); // Returns the robot for manipulation in other classes
	void ChangeCamera(glm::vec3 CameraPosition); // Change which camera is currently being used
	void SetupProjection(int width, int height, bool RobotReady); // Create projection of scene
	void ProcessInput(int input); // Process input of 

	void SetMaterialDefault(); // Set a materials properties

	void SetLightPosition(float x, float y, float z); // Set a light position
	void ConfigureLightSources(); // Sets up openGL light

	int ReturnCollectableCount(); // Returns value of collectables collected

	void ResetCollectableCount(); // Reset collectables count variable

	void Prepare(float dt); // Prepare scene for rendering
	void ResetCollected(); // Reset which collectables are marked as collected
	void Render(); // draw/render scene
};

#endif