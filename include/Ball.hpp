#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "./Corridor.hpp"
#include "./Racket.hpp"
#include "./3D_tools.hpp"
#include "./Obstacle.hpp"

struct Ball {
    void moveBall();
    void followRacketPosition(Racket& racket);
    void drawBall();
    bool isBallCollideObstacleFront(std::vector<Obstacle> level) const;
    bool isBallCollideObstacleBack(std::vector<Obstacle> level) const;
    
    void reset();

    double radius_ball = 0.5;
    double speed_ball = 0.2;
    v3d dir {0, 1., 0};
    v3d pos {0, 0, 0.};

    bool canBallMove = false;
    bool isInLaunchingMode = true;
};