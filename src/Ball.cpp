#include "../include/Ball.hpp"
#include "../include/3D_tools.hpp"


void Ball::reset() {
    dir = v3d {0, 1., 0};
    pos = v3d {0, 0, 0.};
    canBallMove = false;
    isInLaunchingMode = true;
}

void Ball::moveBall() {
    dir.normalize();

    pos.x += dir.x * speed_ball;
    pos.y += dir.y * speed_ball;
    pos.z += dir.z * speed_ball;
}

void Ball::followRacketPosition(Racket& racket) {
    double marginAvance = 0.5;

    pos.x = racket.posMiddle.x;
    pos.y = racket.posMiddle.y + radius_ball + marginAvance;
    pos.z = racket.posMiddle.z;

    dir.x = 0;
    dir.y = 1;
    dir.z = 0;
}

void Ball::drawBall() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);

    GLfloat reflexion_specular[] = {1., 1., 1., 1.};
    GLfloat shininess[] = {128.};

    GLfloat purple[] = {0.53f, 0.16f, 0.88f, 1.f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
    glMaterialfv(GL_FRONT, GL_SPECULAR, reflexion_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glTranslatef(pos.x, pos.y, pos.z);
    glScalef(radius_ball, radius_ball, radius_ball);
    drawSphere();
    glPopMatrix();
}

bool Ball::isBallCollideObstacleFront(std::vector<Obstacle> level) const {
    unsigned int currentSection = (pos.y / WALL_DEPTH);

    if(pos.y < 0 ||
        pos.y > (level.size() * WALL_DEPTH) ||
        currentSection >= level.size()) {
    return false;
    }

    // Ball is inside section with obstacle but have no collision yet
    double marginAvance = 0.2;
    double position_ball = pos.y + radius_ball + marginAvance;

    if(dir.y > 0 && position_ball > (WALL_DEPTH / 2) * (1 + currentSection)) {
        // Ball has collid with wall
 
        auto obstacle = level[currentSection];
        switch(obstacle.type) {
            case TOP_OBSTACLE: if(pos.z + radius_ball >= obstacle.pos.z - obstacle.height / 2) { return true; } break; // TOP
            case BOT_OBSTACLE: if(pos.z - radius_ball <= obstacle.pos.z + obstacle.height / 2) { return true; } break; // BOT
            case RIGHT_OBSTACLE: if(pos.x + radius_ball >= obstacle.pos.x - obstacle.width / 2 ) { return true; } break; // RIGHT
            case LEFT_OBSTACLE: if(pos.x - radius_ball <= obstacle.pos.x + obstacle.width / 2) { return true; } break; // LEFT
            default: break;
        }
    }
    return false;
}


bool Ball::isBallCollideObstacleBack(std::vector<Obstacle> level) const {
    unsigned int currentSection = (pos.y / WALL_DEPTH);

    if(pos.y < 0 ||
        pos.y > (level.size() * WALL_DEPTH) ||
        currentSection >= level.size()) {
    return false;
    }

    // Ball is inside section with obstacle but have no collision yet
    double marginAvance = 0.1;
    double position_ball = pos.y - radius_ball * 2 - marginAvance;

    if(dir.y < 0 && position_ball <= (WALL_DEPTH) * (1 + currentSection)) {
        // Ball has collid with wall
 
        auto obstacle = level[currentSection];
        switch(obstacle.type) {
            case TOP_OBSTACLE: if(pos.z + radius_ball >= obstacle.pos.z - obstacle.height / 2) { return true; } break; // TOP
            case BOT_OBSTACLE: if(pos.z - radius_ball <= obstacle.pos.z + obstacle.height / 2) { return true; } break; // BOT
            case RIGHT_OBSTACLE: if(pos.x + radius_ball >= obstacle.pos.x - obstacle.width / 2 ) { return true; } break; // RIGHT
            case LEFT_OBSTACLE: if(pos.x - radius_ball <= obstacle.pos.x + obstacle.width / 2) { return true; } break; // LEFT
            default: break;
        }
    }
    return false;
}