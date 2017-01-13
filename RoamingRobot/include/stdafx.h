// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <tchar.h>

#include "CGfxOpenGL.h"

// shader.h included these
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML\glew.h>		// make 1.5 functions into function pointers - bind at runtime.
#include <SFML\OpenGL.hpp>	// glew BEFORE opengl headers!!!!
#include <SFML\Graphics.hpp>
// put these inside the SFML\include folder
#include <SFML\wglext.h>
#include <SFML\glext.h>
#include <windows.h>

//#include <gl/gl.h>
//#include <gl/glu.h>


#include "../libraries/glm/glm/glm.hpp"

#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>