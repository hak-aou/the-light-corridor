#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

#include "./Corridor.hpp"
#include "./3D_tools.hpp"
#include "./Obstacle.hpp"

#define LIFE 5
#define RACKET_WIDTH 0.8
#define RACKET_HEIGHT 0.8
#define RACKET_SPEED 0.18

struct Racket {
    void drawRacket();
    void updatePosition(double x_pos, double y_pos, double depth);
    bool isRacketCollideObstacle(std::vector<Obstacle> level);
    void drawPrototypePoint();
    void reset();
    bool isGameFinish(const std::vector<Obstacle> level);

    double racket_width  = RACKET_WIDTH;
    double racket_height = RACKET_HEIGHT;
    double racket_depth  = WALL_DEPTH / 2;

    int life = LIFE;
    double racket_speed = RACKET_SPEED;

    v3d posMiddle      {0, 0, 0};
    v3d posTopLeft     {0, 0, 0};
    v3d posTopRight    {0, 0, 0};
    v3d posBottomLeft  {0, 0, 0};
    v3d posBottomRight {0, 0, 0};

    bool canRacketMove = false;
    bool isRacketBlocked = false;
    bool canPress = true;

    bool isSticky = false;
    double score = 0;
};
