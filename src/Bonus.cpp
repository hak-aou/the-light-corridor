#include "../include/Bonus.hpp"

// Pour l'opacité : https://stackoverflow.com/questions/1617370/how-to-use-alpha-transparency-in-opengl
void Bonus::drawBonus() const {
    v3d color;
    switch(type) {
        case STICKY_BONUS: color = v3d {0., 1., 0.}; break;
        case LIFE_BONUS: color = v3d {1., 0., 0.}; break;
        case SIZE_BONUS: color = v3d {0., 0., 1.}; break;
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);

    GLfloat reflexion_specular[] = {1., 1., 1., 1.};
    GLfloat shininess[] = {128.};

    float opacity = 0.5f;
    GLfloat purple[] = {(float) color.x, (float) color.y, (float) color.z, opacity};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
    glMaterialfv(GL_FRONT, GL_SPECULAR, reflexion_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glTranslatef(pos.x, pos.y, pos.z);
    glScalef(RADIUS_BONUS, RADIUS_BONUS, RADIUS_BONUS);
    drawSphere();
    glPopMatrix();

    glDisable(GL_BLEND); 
}

v3d randPosition(const std::vector<Obstacle>& level) {
    return v3d(rand_min_max_double(-WALL_WIDTH / 2 + RADIUS_BONUS, WALL_WIDTH / 2 - RADIUS_BONUS),
               rand_min_max_double(-WALL_DEPTH, WALL_DEPTH * level.size()),
               rand_min_max_double(-WALL_HEIGHT / 2 + RADIUS_BONUS, WALL_HEIGHT / 2 - RADIUS_BONUS)
    );
}

std::vector<Bonus> generateBonusInLevel(int numberBonus, const std::vector<Obstacle>& level) {
    std::vector<Bonus> listBonusPos;

    for(int i = 0; i < numberBonus; i++) {
        listBonusPos.emplace_back(randPosition(level),
                                  static_cast<BonusType>(rand() % (SIZE_BONUS + 1) )); // static_cast to get random enum in BonusType
    }

    return listBonusPos;
}

void drawAllBonus(const std::vector<Bonus>& listBonus) {
    for(auto& bonus : listBonus) {
        bonus.drawBonus();
    }
}

    void playerGetBonus(std::vector<Bonus>& listBonus, Racket& racket) {
        for (auto it = listBonus.begin(); it != listBonus.end(); ) {
            v3d distance = it->pos.getDistance(racket.posMiddle);

            const bool is_touching = std::abs(distance.x) <= RADIUS_BONUS + racket.racket_width / 2 &&
                                     std::abs(distance.y) <= (RADIUS_BONUS + racket.racket_height / 2) &&
                                     std::abs(distance.z) <= RADIUS_BONUS + racket.racket_height / 2;

            if(is_touching) {
                switch(it->type) {
                    case STICKY_BONUS:
                        racket.isSticky = true;
                        break;

                    case LIFE_BONUS:
                        racket.life++;
                        break;
                    
                    case SIZE_BONUS:
                        racket.racket_width *= 1.2;
                        racket.racket_height *= 1.2;

                        racket.racket_width = clamp(racket.racket_width, 1., WALL_WIDTH / 5);
                        racket.racket_height = clamp(racket.racket_height, 1., WALL_HEIGHT / 5);
                        break;
                }
                racket.score += 50;
                it = listBonus.erase(it);
            } else {
                ++it;
            }
        }
    }