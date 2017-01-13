
#include <stdafx.h>

#include "Robot.h"
#include "timer.h"
#include <SFML/Graphics.hpp>

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
CHiResTimer *g_hiResTimer = NULL;
sf::Clock timerClock;

//int main()
//{
//	sf::Vector2f truck = (sf::Vector2f(1.5f, 1.f, 1.f));
//
//}

int main()
{
	sf::ContextSettings context(depthBits, stencilBits, antiAliasingLevel, majorVersion, minorVersion);
	sf::Window window(sf::VideoMode(windowWidth, windowHeight, 32), "Roaming Robot", 7U, context);
	g_glRender = new CGfxOpenGL;
	g_hiResTimer = new CHiResTimer;
	g_glRender->Init();
	g_hiResTimer->Init();
	
	g_glRender->SetupProjection(windowWidth, windowHeight, false);

	

	while (window.isOpen())
	{
		if (timerClock.getElapsedTime().asSeconds() > 0.005)
		{
			g_glRender->Prepare(timerClock.getElapsedTime().asSeconds());
			g_glRender->Render();
			timerClock.restart();
			
		}
		if (CameraID == 1)
		{
			g_glRender->ChangeCamera(glm::vec3(1, 30, 100));
		}
		else if (CameraID == 2)
		{
			g_glRender->ChangeCamera(glm::vec3(100, 30, -30));
		}

		else if (CameraID == 3)
		{
			g_glRender->ChangeCamera(glm::vec3(-100, 30, 30));
		}
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}

			// Resize event : adjust viewport
			if (Event.type == sf::Event::Resized)
			{
				g_glRender->SetupProjection(windowWidth, windowHeight, false);

			}

			if ((Event.type == sf::Event::MouseButtonPressed) && (Event.key.code == sf::Mouse::Button::Left))
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
			if ((Event.type == sf::Event::MouseButtonPressed) && (Event.key.code == sf::Mouse::Button::Right))
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
			if ((Event.type == sf::Event::KeyReleased) && (Event.key.code == sf::Keyboard::Up))
			{
				g_glRender->ReturnRobot()->ToggleAllMovement();
				g_glRender->ReturnRobot()->Moving = false;
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Escape)
				{
					PostQuitMessage(0);
				}
				if (Event.key.code == sf::Keyboard::Up)
				{
					g_glRender->ProcessInput(VK_UP);
				}

				if (Event.key.code == sf::Keyboard::Down)
				{
					g_glRender->ProcessInput(VK_DOWN);
				}

				if (Event.key.code == sf::Keyboard::Left)
				{
					g_glRender->ProcessInput(VK_LEFT);
				}

				if (Event.key.code == sf::Keyboard::Right)
				{
					g_glRender->ProcessInput(VK_RIGHT);
				}

			}
			

		}
		
		window.display();
	}
}



//bool exiting = false;
//long windowWidth = 1024;
//long windowHeight = 768;
//unsigned int CameraID = 1;
//long windowBits = 32;
//bool fullscreen = false;
//bool walking = false;
//HDC hDC;
//
//CGfxOpenGL *g_glRender = NULL;
//CHiResTimer *g_hiResTimer = NULL;
//
//
//void SetupPixelFormat(HDC hDC)
//{
//	int pixelFormat;
//
//	PIXELFORMATDESCRIPTOR pfd =
//	{	
//		sizeof(PIXELFORMATDESCRIPTOR),	// size
//			1,							// version
//			PFD_SUPPORT_OPENGL |		// OpenGL window
//			PFD_DRAW_TO_WINDOW |		// render to window
//			PFD_DOUBLEBUFFER,			// support double-buffering
//			PFD_TYPE_RGBA,				// color type
//			32,							// prefered color depth
//			0, 0, 0, 0, 0, 0,			// color bits (ignored)
//			0,							// no alpha buffer
//			0,							// alpha bits (ignored)
//			0,							// no accumulation buffer
//			0, 0, 0, 0,					// accum bits (ignored)
//			16,							// depth buffer
//			0,							// no stencil buffer
//			0,							// no auxiliary buffers
//			PFD_MAIN_PLANE,				// main layer
//			0,							// reserved
//			0, 0, 0,					// no layer, visible, damage masks
//	};
//
//	pixelFormat = ChoosePixelFormat(hDC, &pfd);
//	SetPixelFormat(hDC, pixelFormat, &pfd);
//}

//LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	int wmId; // Holds ID of menu item clicked
//	static HDC hDC;
//	static HGLRC hRC;
//	int height, width;
//	
//
//	// dispatch messages
//	switch (uMsg)
//	{	
//	case WM_CREATE:			// window creation
//		hDC = GetDC(hWnd);
//		SetupPixelFormat(hDC);
//		//SetupPalette();
//		hRC = wglCreateContext(hDC);
//		wglMakeCurrent(hDC, hRC);
//		break;
//
//	
//
//	case WM_DESTROY:			// window destroy
//	case WM_QUIT:
//	case WM_CLOSE:					// windows is closing
//
//		// deselect rendering context and delete it
//		wglMakeCurrent(hDC, NULL);
//		wglDeleteContext(hRC);
//
//		// send WM_QUIT to message queue
//		PostQuitMessage(0);
//		break;
//		
//	case WM_COMMAND:
//	
//				break;
//
//
//		break;
//	case WM_SIZE:
//		height = HIWORD(lParam);		// retrieve width and height
//		width = LOWORD(lParam);
//
//		g_glRender->SetupProjection(width, height, false);
//
//		break;
//
//	case WM_ACTIVATEAPP:		// activate app
//		break;
//
//	case WM_PAINT:				// paint
//		PAINTSTRUCT ps;
//		BeginPaint(hWnd, &ps);
//		EndPaint(hWnd, &ps);
//		break;
//
//	case WM_LBUTTONDOWN:		// left mouse button
//		if (CameraID == 3)
//		{
//			CameraID = 1;
//		}
//		else
//		{
//			CameraID++;
//		}
//		break;
//
//	case WM_RBUTTONDOWN:		// right mouse button
//		if (CameraID == 1)
//		{
//			CameraID = 3;
//		}
//		else
//		{
//			CameraID--;
//		}
//		break;
//
//	case WM_MOUSEMOVE:			// mouse movement
//		break;
//
//	case WM_LBUTTONUP:			// left button release
//		
//		break;
//
//	case WM_RBUTTONUP:			// right button release
//		break;
//
//	case WM_KEYUP:
//	
//		int kuKeys;
//		LPARAM kukeyData;
//		kuKeys = (int)wParam;    // virtual-key code 
//		kukeyData = lParam;          // key data 
//
//		switch (kuKeys)
//		{
//		case VK_UP:
//			g_glRender->ReturnRobot()->ToggleAllMovement();
//			g_glRender->ReturnRobot()->Moving = false;
//			break;
//		}
//
//		//g_glRender->ReturnRobot()->ToggleAllMovement();
//		break;
//
//
//	case WM_KEYDOWN:
//		int fwKeys;
//		LPARAM keyData;
//		fwKeys = (int)wParam;    // virtual-key code 
//		keyData = lParam;          // key data 
//
//		switch(fwKeys)
//		{
//			// Quit Application
//		case VK_ESCAPE:
//			PostQuitMessage(0);
//			break;
//
//			//  Pause arm movement
//		case VK_SPACE:
//			g_glRender->ReturnRobot()->ToggleAllMovement();
//			
//			break;
//
//			//Proccess keys relating to movement
//		default:
//			//g_glRender->ReturnRobot()->ToggleAllMovement();
//			g_glRender->ProcessInput(fwKeys);
//		}
//
//		break;
//
//	default:
//		break;
//	}
//
//	return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	WNDCLASSEX windowClass;		// window class
//	HWND	   hwnd;			// window handle
//	MSG		   msg;				// message
//	RECT	   windowRect;
//
//	g_glRender = new CGfxOpenGL;
//	g_hiResTimer = new CHiResTimer;
//
//	windowRect.left=(long)0;						// Set Left Value To 0
//	windowRect.right=(long)windowWidth;	// Set Right Value To Requested Width
//	windowRect.top=(long)0;							// Set Top Value To 0
//	windowRect.bottom=(long)windowHeight;	// Set Bottom Value To Requested Height
//
//	// fill out the window class structure
//	windowClass.cbSize			= sizeof(WNDCLASSEX);
//	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
//	windowClass.lpfnWndProc		= MainWindowProc;
//	windowClass.cbClsExtra		= 0;
//	windowClass.cbWndExtra		= 0;
//	windowClass.hInstance		= hInstance;
//	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	// default icon
//	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
//	windowClass.hbrBackground	= NULL;								// don't need background
//	windowClass.lpszMenuName	= NULL;								// no menu
//	windowClass.lpszClassName	= "GLClass";
//	windowClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);		// windows logo small icon
//
//	// register the windows class
//	if (!RegisterClassEx(&windowClass))
//		return 0;
//
//
//	// class registered, so now create our window
//	hwnd = CreateWindowEx(NULL, 								// extended style
//		"GLClass",							// class name
//		"Roaming Robot",	// app name
//		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN |
//		WS_CLIPSIBLINGS,
//		0, 0,								// x,y coordinate
//		windowRect.right - windowRect.left,
//		windowRect.bottom - windowRect.top, // width, height
//		NULL,								// handle to parent
//		NULL,								// handle to menu
//		hInstance,							// application instance
//		NULL);								// no extra params
//
//	hDC = GetDC(hwnd);
//
//	// check if window creation failed (hwnd would equal NULL)
//	if (!hwnd)
//		return 0;
//
//	ShowWindow(hwnd, SW_SHOW);			// display the window
//	UpdateWindow(hwnd);					// update the window
//
//	g_glRender->Init();
//	g_hiResTimer->Init();
//
//	while (!exiting)
//	{
//		g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
//		g_glRender->Render();
//		SwapBuffers(hDC);
//
//		if (CameraID == 1)
//		{
//			g_glRender->ChangeCamera(glm::vec3(1, 30, 100));
//		}
//		else if (CameraID == 2)
//		{
//			g_glRender->ChangeCamera(glm::vec3(100, 30, -30));
//		}
//
//		else if (CameraID == 3)
//		{
//			g_glRender->ChangeCamera(glm::vec3(-100, 30, 30));
//		}
//
//		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
//		{
//			if (!GetMessage (&msg, NULL, 0, 0))
//			{
//				exiting = true;
//				break;
//			}
//
//			TranslateMessage (&msg);
//			DispatchMessage (&msg);
//		}
//	}
//
//	delete g_glRender;
//
//	return (int)msg.wParam;
//}
