#ifndef __GL_COMPONENT
#define __GL_COMPONENT



#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0


class Robot;

class Scene;

class CGfxOpenGL
{
private:
	float _fRotationAngle;

	int m_windowWidth;
	int m_windowHeight;
	Robot *theRobot;
	Scene *theScene;

public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	

	bool Init();
	bool Shutdown();
	Robot* ReturnRobot();
	void SetupProjection(int width, int height);
	void ProcessInput(int input);

	void Prepare(float dt);
	void Render();
};

#endif