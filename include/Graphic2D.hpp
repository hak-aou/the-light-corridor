#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <map>

enum Action {
    PLAY, CONTINUE, NEWGAME, QUIT, WAIT_CLICK
};

enum State {
    MENU_BEGIN,
    MENU_WIN,
    MENU_DEFEAT,
    PLAYING
};

void drawMenu(double view_size);
void drawVictoryMenu(int score, double view_size);
void drawDefeatMenu(int score, double view_size);
Action detectClick(double x_pos, double y_pos, State state);
void drawLife(double depth, int life);

void drawScore(int number, double depth);