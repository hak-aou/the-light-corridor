#include "../include/3D_tools.hpp"
#include "../include/Texture.hpp"
#include "../include/Obstacle.hpp"
#include "../include/Corridor.hpp"

void drawObstacle(Obstacle obstacle) {
    auto textureObstacle = getTexture("../assets/obstacle_img.jpg");

    glPushMatrix();
    glColor3f(0.3, 0., 0.8);
    glTranslatef(obstacle.pos.x, obstacle.pos.y, obstacle.pos.z);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(obstacle.width, obstacle.height, 1.0);
    drawFrame();
    drawSquareTexture(textureObstacle, 1.);
    glPopMatrix();
}