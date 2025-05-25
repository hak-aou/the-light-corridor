#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "./Obstacle.hpp"
#include "./Corridor.hpp"

std::vector<Obstacle> generateLevel(int numberSection);