#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include "./3D_tools.hpp"

enum TypeObstacle {
    TOP_OBSTACLE,
    BOT_OBSTACLE,
    RIGHT_OBSTACLE,
    LEFT_OBSTACLE,
    NOTHING
};

struct Obstacle {
    Obstacle(double new_width, double new_height, v3d new_pos, TypeObstacle new_type) :
        width {new_width},
        height {new_height},
        pos {new_pos},
        type {new_type}
    {}

    double width;
    double height;
    v3d pos;
    TypeObstacle type;
};

void drawObstacle(Obstacle type);