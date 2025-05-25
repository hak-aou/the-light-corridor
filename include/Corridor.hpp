#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "./Obstacle.hpp"

static const double WALL_DEPTH = 5.0;  // y
static const double WALL_WIDTH = 11.0; // x
static const double WALL_HEIGHT = 6.0; // z

void drawFrame();
void drawOneSection();
void drawMultipleSection(const std::vector<Obstacle>& level);
void drawEndSection();