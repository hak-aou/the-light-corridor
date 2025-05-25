#include "../include/Racket.hpp"
#include "../include/3D_tools.hpp"


void Racket::reset() {
    life = LIFE;
    racket_width  = RACKET_WIDTH;
    racket_height = RACKET_HEIGHT;
    racket_depth  = -WALL_DEPTH / 2;

    life = LIFE;
    racket_speed = RACKET_SPEED;

    score = 0;
    posMiddle      = {0, 0, 0};
    posTopLeft     = {0, 0, 0};
    posTopRight    = {0, 0, 0};
    posBottomLeft  = {0, 0, 0};
    posBottomRight = {0, 0, 0};
}

bool Racket::isRacketCollideObstacle(std::vector<Obstacle> level) {
    double racketDepthByOrigin = (posMiddle.y + WALL_DEPTH / 2);
    
    double marginAvance = 0.8;
    int currentSection = racketDepthByOrigin / WALL_DEPTH;
    if(currentSection >= (int) level.size()) { return false; } // ball depasse le niveau

    if(racketDepthByOrigin < WALL_DEPTH * (1 + currentSection) - marginAvance) {
        return false;
    }

    auto obstacle = level[currentSection];
    switch(obstacle.type) {
            case TOP_OBSTACLE: if(posMiddle.z + racket_height >= obstacle.pos.z - obstacle.height / 2) { return true; } break; // TOP
            case BOT_OBSTACLE: if(posMiddle.z - racket_height <= obstacle.pos.z + obstacle.height / 2) { return true; } break; // BOT
            case RIGHT_OBSTACLE: if(posMiddle.x + racket_width >= obstacle.pos.x - obstacle.width / 2 ) { return true; } break; // RIGHT
            case LEFT_OBSTACLE: if(posMiddle.x - racket_width <= obstacle.pos.x + obstacle.width / 2) { return true; } break; // LEFT
        default: break;
    }
    return false;
}


void Racket::updatePosition(double x_pos, double y_pos, double depth) { 
    posMiddle.x = x_pos;
    posMiddle.y = racket_depth + depth;
    posMiddle.z = y_pos;

    double margin = 0.05;

    posMiddle.x = clamp(posMiddle.x, -WALL_WIDTH / 2 + racket_width + margin, WALL_WIDTH / 2 - racket_width - margin);
    posMiddle.z = clamp(posMiddle.z, -WALL_HEIGHT / 2 + racket_height + margin, WALL_HEIGHT / 2 - racket_height - margin);
    
    posTopLeft = {posMiddle.x - racket_width, posMiddle.y, posMiddle.z + racket_height};
    posTopRight = {posMiddle.x + racket_width, posMiddle.y, posMiddle.z + racket_height};
    posBottomLeft = {posMiddle.x - racket_width, posMiddle.y, posMiddle.z - racket_height};
    posBottomRight = {posMiddle.x + racket_width, posMiddle.y, posMiddle.z - racket_height};
}

void Racket::drawPrototypePoint() {
    double size = 0.02;

    glColor3f(0., 0., 0.);

    // Middle
    glPushMatrix();
    glTranslatef(posMiddle.x, posMiddle.y, posMiddle.z);
    glScalef(size, size, size);
    drawSphere();
    glPopMatrix();

    // Top left
    glPushMatrix();
    glTranslatef(posTopLeft.x, posTopLeft.y, posTopLeft.z);
    glScalef(size, size, size);
    drawSphere();
    glPopMatrix();

    // Top right
    glPushMatrix();
    glTranslatef(posTopRight.x, posTopRight.y, posTopRight.z);
    glScalef(size, size, size);
    drawSphere();
    glPopMatrix();

    // Bot left
    glPushMatrix();
    glTranslatef(posBottomLeft.x, posBottomLeft.y, posBottomLeft.z);
    glScalef(size, size, size);
    drawSphere();
    glPopMatrix();

    // Bot right
    glPushMatrix();
    glTranslatef(posBottomRight.x, posBottomRight.y, posBottomRight.z);
    glScalef(size, size, size);
    drawSphere();
    glPopMatrix();
}


void Racket::drawRacket() {
    glDisable(GL_LIGHTING);

    glPushMatrix();
    drawPrototypePoint();
        glBegin(GL_LINE_LOOP);
            glColor3f(1., 1., 1.);
            glVertex3f(posTopLeft.x, posTopLeft.y, posTopLeft.z);
            glVertex3f(posTopRight.x, posTopRight.y, posTopRight.z);
            glVertex3f(posBottomRight.x, posBottomRight.y, posBottomRight.z);
            glVertex3f(posBottomLeft.x, posBottomLeft.y, posBottomLeft.z);
        glEnd();
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

bool Racket::isGameFinish(const std::vector<Obstacle> level) {
    unsigned int currentSection = (posMiddle.y / WALL_DEPTH);
    return currentSection >= level.size();
}