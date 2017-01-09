#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <stdafx.h>


#include "Robot.h"
#include "timer.h"
#include "resource.h"



bool exiting = false;
long windowWidth = 1024;
long windowHeight = 768;
unsigned int CameraID = 1;
long windowBits = 32;
bool fullscreen = false;
bool walking = false;
HDC hDC;

CGfxOpenGL *g_glRender = NULL;
CHiResTimer *g_hiResTimer = NULL;


void SetupPixelFormat(HDC hDC)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{	
		sizeof(PIXELFORMATDESCRIPTOR),	// size
			1,							// version
			PFD_SUPPORT_OPENGL |		// OpenGL window
			PFD_DRAW_TO_WINDOW |		// render to window
			PFD_DOUBLEBUFFER,			// support double-buffering
			PFD_TYPE_RGBA,				// color type
			32,							// prefered color depth
			0, 0, 0, 0, 0, 0,			// color bits (ignored)
			0,							// no alpha buffer
			0,							// alpha bits (ignored)
			0,							// no accumulation buffer
			0, 0, 0, 0,					// accum bits (ignored)
			16,							// depth buffer
			0,							// no stencil buffer
			0,							// no auxiliary buffers
			PFD_MAIN_PLANE,				// main layer
			0,							// reserved
			0, 0, 0,					// no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId; // Holds ID of menu item clicked
	static HDC hDC;
	static HGLRC hRC;
	int height, width;
	

	// dispatch messages
	switch (uMsg)
	{	
	case WM_CREATE:			// window creation
		hDC = GetDC(hWnd);
		SetupPixelFormat(hDC);
		//SetupPalette();
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		break;

	

	case WM_DESTROY:			// window destroy
	case WM_QUIT:
	case WM_CLOSE:					// windows is closing

		// deselect rendering context and delete it
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		// send WM_QUIT to message queue
		PostQuitMessage(0);
		break;
		
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		//wmEvent = HIWORD(wParam);
		switch (wmId)
		{
			// If menu item selected toggle robots animation
			case ID_ROBOT_TOGGLEALLROBOTMOVEMENT:
				g_glRender->ReturnRobot()->ToggleAllMovement();
				break;

		}

		break;
	case WM_SIZE:
		height = HIWORD(lParam);		// retrieve width and height
		width = LOWORD(lParam);

		g_glRender->SetupProjection(width, height, false);

		break;

	case WM_ACTIVATEAPP:		// activate app
		break;

	case WM_PAINT:				// paint
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:		// left mouse button
		if (CameraID == 3)
		{
			CameraID = 1;
		}
		else
		{
			CameraID++;
		}
		break;

	case WM_RBUTTONDOWN:		// right mouse button
		if (CameraID == 1)
		{
			CameraID = 3;
		}
		else
		{
			CameraID--;
		}
		break;

	case WM_MOUSEMOVE:			// mouse movement
		break;

	case WM_LBUTTONUP:			// left button release
		
		break;

	case WM_RBUTTONUP:			// right button release
		break;

	case WM_KEYUP:
	
		int kuKeys;
		LPARAM kukeyData;
		kuKeys = (int)wParam;    // virtual-key code 
		kukeyData = lParam;          // key data 

		switch (kuKeys)
		{
		case VK_UP:
			g_glRender->ReturnRobot()->ToggleAllMovement();
			g_glRender->ReturnRobot()->Moving = false;
			break;
		}

		//g_glRender->ReturnRobot()->ToggleAllMovement();
		break;


	case WM_KEYDOWN:
		int fwKeys;
		LPARAM keyData;
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		switch(fwKeys)
		{
			// Quit Application
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

			//  Pause arm movement
		case VK_SPACE:
			g_glRender->ReturnRobot()->ToggleAllMovement();
			
			break;

			//Proccess keys relating to movement
		default:
			//g_glRender->ReturnRobot()->ToggleAllMovement();
			g_glRender->ProcessInput(fwKeys);
		}

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;		// window class
	HWND	   hwnd;			// window handle
	MSG		   msg;				// message
	RECT	   windowRect;

	g_glRender = new CGfxOpenGL;
	g_hiResTimer = new CHiResTimer;

	windowRect.left=(long)0;						// Set Left Value To 0
	windowRect.right=(long)windowWidth;	// Set Right Value To Requested Width
	windowRect.top=(long)0;							// Set Top Value To 0
	windowRect.bottom=(long)windowHeight;	// Set Bottom Value To Requested Height

	// fill out the window class structure
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc		= MainWindowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	// default icon
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground	= NULL;								// don't need background
	windowClass.lpszMenuName	= NULL;								// no menu
	windowClass.lpszClassName	= "GLClass";
	windowClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);		// windows logo small icon

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;


	// class registered, so now create our window
	hwnd = CreateWindowEx(NULL, 								// extended style
		"GLClass",							// class name
		"Roaming Robot",	// app name
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,								// x,y coordinate
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, // width, height
		NULL,								// handle to parent
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),								// handle to menu
		hInstance,							// application instance
		NULL);								// no extra params

	hDC = GetDC(hwnd);

	// check if window creation failed (hwnd would equal NULL)
	if (!hwnd)
		return 0;

	ShowWindow(hwnd, SW_SHOW);			// display the window
	UpdateWindow(hwnd);					// update the window

	g_glRender->Init();
	g_hiResTimer->Init();

	while (!exiting)
	{
		g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
		g_glRender->Render();
		SwapBuffers(hDC);

		if (CameraID == 1)
		{
			g_glRender->ChangeCamera(glm::vec3(10, 10, 10));
		}
		else if (CameraID == 2)
		{
			g_glRender->ChangeCamera(glm::vec3(-10, 10, -10));
		}

		else if (CameraID == 3)
		{
			g_glRender->ChangeCamera(glm::vec3(-30, 10, 30));
		}

		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				exiting = true;
				break;
			}

			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}

	delete g_glRender;

	return (int)msg.wParam;
}