#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "./Corridor.hpp"
#include "./Ball.hpp"
#include "./Racket.hpp"
#include "./3D_tools.hpp"
#include "./Obstacle.hpp"

enum BonusType {
    STICKY_BONUS,
    LIFE_BONUS,
    SIZE_BONUS
};

#define RADIUS_BONUS 1

struct Bonus {
    void drawBonus() const;
    Bonus(v3d new_pos, BonusType new_type) :
        pos { new_pos },
        type { new_type}
        {}

    v3d pos {0, 0, 0.};
    BonusType type;
};

v3d randPosition(const std::vector<Obstacle>& level);
std::vector<Bonus> generateBonusInLevel(int numberBonus, const std::vector<Obstacle>& level);
void drawAllBonus(const std::vector<Bonus>& listBonus);
void playerGetBonus(std::vector<Bonus>& listBonus, Racket& racket);