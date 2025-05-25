#include "../include/Collision.hpp"

// bool ballHasTouchRacket(const Ball& ball, const Racket& racket) {
//     v3d distance = ball.pos.getDistance(racket.posMiddle);

//     return std::abs(distance.x) <= ball.radius_ball + racket.racket_width  &&
//            ball.pos.y - ball.radius_ball <= racket.posMiddle.y &&
//            std::abs(distance.z) <= ball.radius_ball + racket.racket_height ;
// }

bool ballHasTouchRacket(const Ball& ball, const Racket& racket) {
    bool xCondition = (ball.pos.x >= racket.posBottomLeft.x && ball.pos.x <= racket.posTopRight.x) ||
                      (ball.pos.x + ball.radius_ball >= racket.posBottomLeft.x && ball.pos.x + ball.radius_ball <= racket.posTopRight.x) ||
                      (ball.pos.x - ball.radius_ball >= racket.posBottomLeft.x && ball.pos.x - ball.radius_ball <= racket.posTopRight.x);
    
    bool yCondition = ball.pos.y - ball.radius_ball <= racket.posMiddle.y;
    
    bool zCondition = (ball.pos.z >= racket.posBottomLeft.z && ball.pos.z <= racket.posTopRight.z) ||
                      (ball.pos.z + ball.radius_ball >= racket.posBottomLeft.z && ball.pos.z + ball.radius_ball <= racket.posTopRight.z) ||
                      (ball.pos.z - ball.radius_ball >= racket.posBottomLeft.z && ball.pos.z - ball.radius_ball <= racket.posTopRight.z);

    return xCondition && yCondition && zCondition;
}

v3d getImpactePosition(const Ball& ball, const Racket& racket) {
    double x = clamp(ball.pos.x, racket.posBottomLeft.x, racket.posTopRight.x);
    double y = ball.pos.y;
    double z = clamp(ball.pos.z, racket.posBottomLeft.z, racket.posTopRight.z);

    return v3d {x, y, z};
}

v3d getNewDirection(const Racket& racket, v3d impact_position) {
    double distance_x = impact_position.x - racket.posMiddle.x;
    double distance_z = impact_position.z - racket.posMiddle.z;

    double ratio_x = distance_x / racket.racket_width;
    double ratio_z = distance_z / racket.racket_height;

    return v3d {ratio_x, 1, ratio_z};
}

bool ballExitCamera(const Ball& ball, const Racket& racket, double depth) {
    return ballHasTouchRacket(ball, racket) == false &&
           ball.pos.y + ball.radius_ball * 2 < racket.racket_depth + depth;
}

void doBallBounceRacket(Ball& ball, v3d new_dir) {
    ball.dir.x = new_dir.x;
    ball.dir.y *= -1;
    ball.dir.z = new_dir.z;
}

void drawImpact(v3d impacte) {
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glColor3f(1., 1., 1.);
    glTranslatef(impacte.x, impacte.y - 0.3, impacte.z);
    glScalef(0.2, 0.2, 0.2);
    drawSphere();
    glPopMatrix();

    glEnable(GL_LIGHTING);
}


v3d getNormalWhenCollide(std::vector<Obstacle> level, const Ball& ball) {
    if(ball.pos.z + ball.radius_ball >= WALL_HEIGHT / 2)  { return v3d {0, 0, -1}; } // TOP
    if(ball.pos.z - ball.radius_ball <= -WALL_HEIGHT / 2) { return v3d {0, 0, 1};  } // BOT
    if(ball.pos.x + ball.radius_ball >= WALL_WIDTH / 2)   { return v3d {-1, 0, 0}; } // RIGht
    if(ball.pos.x - ball.radius_ball <= -WALL_WIDTH / 2)  { return v3d {1, 0, 0};  } // LEFT

    if(ball.isBallCollideObstacleFront(level)) { return v3d {0, -1, 0}; }
    if(ball.isBallCollideObstacleBack(level)) { return v3d {0, 1, 0}; }

    return v3d {-1, -1, -1}; // did not collide anything
}

void doBallBounceWall(Ball& ball, v3d normal_wall) {
    if(normal_wall.x == -1 && normal_wall.y == -1 && normal_wall.z == -1) { return; } // ignore

    v3d temp = v3d(2. * ball.dir.dot(normal_wall) * normal_wall.x,
                   2. * ball.dir.dot(normal_wall) * normal_wall.y,
                   2. * ball.dir.dot(normal_wall) * normal_wall.z);
    ball.dir.vectSub(temp);
    ball.dir.normalize();
}