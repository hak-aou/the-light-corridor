#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include "./3D_tools.hpp"

#define MY_PI 3.141592653f


#define STEP_TIME	0.32f
#define STEP_ANGLE	MY_PI/90.0
#define STEP_PROF	MY_PI/90.0

void makeLight(v3d positionVector, v3d color, GLenum numLight);