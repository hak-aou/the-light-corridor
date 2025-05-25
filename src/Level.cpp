#include "../include/Level.hpp"

std::vector<Obstacle> generateLevel(int numberSection) {
    std::vector<Obstacle> listObstacle;

    for(int i = 0; i < numberSection; i++) {
        double width, height;
        v3d pos;

        if(rand_min_max_int(1, 2) != 1) {
            listObstacle.emplace_back(0, 0, v3d{}, NOTHING);
            continue;
        }
        switch (rand_min_max_int(1, 4)) {
            case 1: // TOP
                height = rand_min_max_double(WALL_HEIGHT / 6, WALL_HEIGHT / 2);
                pos = v3d(0., WALL_DEPTH / 2, WALL_HEIGHT / 2 - height / 2);
                listObstacle.emplace_back(WALL_WIDTH, height, pos, TOP_OBSTACLE);
                break;
            case 2: // BOT
                height = rand_min_max_double(WALL_HEIGHT / 6, WALL_HEIGHT / 2);
                pos = v3d(0., WALL_DEPTH / 2, -WALL_HEIGHT / 2 + height / 2);
                listObstacle.emplace_back(WALL_WIDTH, height, pos, BOT_OBSTACLE);
                break;
            case 3: // RIGHT
                width = rand_min_max_double(WALL_WIDTH / 6, WALL_WIDTH / 2);
                pos = v3d(WALL_WIDTH / 2 - width / 2, WALL_DEPTH / 2, 0);
                listObstacle.emplace_back(width, WALL_HEIGHT, pos, RIGHT_OBSTACLE);
                break;
            case 4: // LEFT
                width = rand_min_max_double(WALL_WIDTH / 6, WALL_WIDTH / 2);
                pos = v3d(-WALL_WIDTH / 2 + width / 2, WALL_DEPTH / 2, 0);
                listObstacle.emplace_back(width, WALL_HEIGHT, pos, LEFT_OBSTACLE);
                break;
        }
    }

    return listObstacle;
}