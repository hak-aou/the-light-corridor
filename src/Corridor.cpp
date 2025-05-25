#include "../include/Corridor.hpp"
#include "../include/3D_tools.hpp"
#include "../include/Texture.hpp"
#include "../include/Obstacle.hpp"
#include <vector>

#define PI 3.14159265
#define PI2 PI * 2

void drawFrame() {
    glBegin(GL_LINES);     // Axe X
    glColor3f(1., 0., 0.); // Red
    glVertex3f(-100., 0., 0.1);
    glVertex3f(100, 0., 0.1);
    glEnd();

    glBegin(GL_LINES);     // Axe Y
    glColor3f(0., 1., 0.); // Green
    glVertex3f(0., -100, 0.1);
    glVertex3f(0., 100, 0.1);
    glEnd();

    glBegin(GL_LINES);     // Axe Z
    glColor3f(0., 0., 1.); // Blue
    glVertex3f(0., 0., -100);
    glVertex3f(0., 0., 100);
    glEnd();
}

void drawOneSection() {
    auto textureWall = getTexture("../assets/wall_img.jpg");

    /* Floor */
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); // Green
    glTranslatef(0.0, 0.0, -WALL_HEIGHT/2);
    glScalef(WALL_WIDTH, WALL_DEPTH, 1.0);
    drawSquareTexture(textureWall, 1.);
    glPopMatrix();

    /* Roof */
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Red
    glTranslatef(0.0, 0.0, WALL_HEIGHT/2);
    glRotatef(-180, 0.0, 1.0, 0.0);
    glScalef(WALL_WIDTH, WALL_DEPTH, 1.0);
    drawSquareTexture(textureWall, 1.);
    glPopMatrix();

    /* Right Wall */
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // White
    glTranslatef(WALL_WIDTH / 2, 0.0, 0.0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(WALL_HEIGHT, WALL_DEPTH, 1.0);
    drawSquareTexture(textureWall, 1.);
    glPopMatrix();

    /* Left Wall */
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0); // Blue
    glTranslatef(-WALL_WIDTH / 2, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glScalef(WALL_HEIGHT, WALL_DEPTH, 1.0);
    drawSquareTexture(textureWall, 1.);
    glPopMatrix();

    glPushMatrix();
    // drawFrame();
    glPopMatrix();
}

void drawMultipleSection(const std::vector<Obstacle>& level) {
    /* One section to mask the 'sky' to the camera at the beginning */
    glPushMatrix();
    glTranslatef(0., -WALL_DEPTH, 0);
    drawOneSection();
    glPopMatrix();

    glPushMatrix();
    for(auto obstacle : level) {
        drawObstacle(obstacle);
        drawOneSection();
        glTranslatef(0., WALL_DEPTH, 0);
    }

    // Section to fill the void
    for(int i = 0; i < 5; i++) {
        drawOneSection();
        glTranslatef(0., WALL_DEPTH, 0);
    }
        glTranslatef(0., -WALL_DEPTH, 0);
    drawEndSection();

    glPopMatrix();
}

void drawEndSection() {
    auto textureWall = getTexture("../assets/wall_img.jpg");

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(WALL_WIDTH, WALL_HEIGHT, 1.);
    drawSquareTexture(textureWall, 1.);
    glPopMatrix();
}