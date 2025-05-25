#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <tuple>
#include "./Ball.hpp"
#include "./Racket.hpp"
#include "./3D_tools.hpp"


bool ballHasTouchRacket(const Ball& ball, const Racket& racket);
bool ballExitCamera(const Ball& ball, const Racket& racket, double depth);
void doBallBounceRacket(Ball& ball, v3d new_dir);
v3d getImpactePosition(const Ball& ball, const Racket& racket);
v3d getNewDirection(const Racket& racket, v3d impact_position);
void drawImpact(v3d impacte);

v3d getNormalWhenCollide(std::vector<Obstacle> level, const Ball& ball);
void doBallBounceWall(Ball& ball, v3d normal_wall);