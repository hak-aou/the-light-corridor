#include "../include/Graphic2D.hpp"
#include "../include/3D_tools.hpp"
#include "../include/Corridor.hpp"
#include "../include/Texture.hpp"

// MENU
// VICTOIRE
// DEFAITE

// view_size = 6
void drawMenu(double view_size) {
    auto textureBackground = getTexture("../assets/background_img.jpg");
    auto texturePlay = getTexture("../assets/play_img.jpg");
    auto textureQuit = getTexture("../assets/quit_img.jpg");

    glDisable(GL_LIGHTING);

    /* Background image */
    glPushMatrix();
    glColor3f(0., 0., 0.);
    glTranslatef(0.0, 1., 0.);
    glRotatef(90, 1., 0., 0.);
    glScalef(20., 11., 1.);
    drawSquareTexture(textureBackground, 1.);
    glPopMatrix();

    /* Play button */
    glPushMatrix();
    glColor3f(0.1, 0.8, 0.1);
    glTranslatef(0.0, 0.0, 1);
    glRotatef(90, 1., 0., 0.);
    glScalef(view_size / 2, 1., 0.);
    drawSquareTexture(texturePlay, 1.);
    glPopMatrix();

    /* Quit button */
    glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    glTranslatef(0.0, 0.0, -1);
    glRotatef(90, 1., 0., 0.);
    glScalef(view_size / 2, 1., 0.);
    drawSquareTexture(textureQuit, 1.);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void drawVictoryMenu(int score, double view_size) {
    auto textureContinue = getTexture("../assets/continue_img.jpg");
    auto textureQuit = getTexture("../assets/quit_img.jpg");

    glDisable(GL_LIGHTING);

    /* Continue button */
    glPushMatrix();
    glColor3f(0.1, 0.8, 0.1);
    glTranslatef(0.0, 0.0, 1);
    glRotatef(90, 1., 0., 0.);
    glScalef(view_size / 2, 1., 0.);
    drawSquareTexture(textureContinue, 1.);
    glPopMatrix();

    /* Quit button */
    glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    glTranslatef(0.0, 0.0, -1);
    glRotatef(90, 1., 0., 0.);
    glScalef(view_size / 2, 1., 0.);
    drawSquareTexture(textureQuit, 1.);
    glPopMatrix();

    drawScore(score, -1);
    glEnable(GL_LIGHTING);
}

void drawDefeatMenu(int score, double view_size) {
    glDisable(GL_LIGHTING);

    auto textureNewGame = getTexture("../assets/new_game_img.jpg");
    auto textureQuit = getTexture("../assets/quit_img.jpg");

    /* New game button */
    glPushMatrix();
    glColor3f(0.1, 0.8, 0.1);
    glTranslatef(0.0, 0.0, 1);
    glRotatef(90, 1., 0., 0.);
    glScalef(view_size / 2, 1., 0.);
    drawSquareTexture(textureNewGame, 1.);
    glPopMatrix();

    /* Quit button */
    glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    glTranslatef(0.0, 0.0, -1);
    glRotatef(90, 1., 0., 0.);
    glScalef(view_size / 2, 1., 0.);
    drawSquareTexture(textureQuit, 1.);
    glPopMatrix();

    drawScore(score, -1);
    glEnable(GL_LIGHTING);
}

Action detectClick(double x_pos, double y_pos, State state) {
    if((x_pos > -1. && x_pos < 1.) && (y_pos > 0.3 && y_pos < 1)) {
        switch(state) {
            case MENU_BEGIN:
                return PLAY;
            case MENU_WIN:
                return CONTINUE;
            case MENU_DEFEAT:
                return NEWGAME;
            default:
              break;
        }
    }

    if((x_pos > -1. && x_pos < 1.) && (y_pos < -0.3 && y_pos > -1)) {
        return QUIT;
    }
    return WAIT_CLICK;
}

void drawLife(double depth, int life) {
    if(life <= 0) { return; }
    auto textureLife = getTexture("../assets/life_img.jpg");
    double radius = 0.4;
    double opacity = 0.7;

    glDisable(GL_LIGHTING);

    for(int i = 0; i < life; i++) {
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-WALL_WIDTH / 2 + radius + i * radius, depth - 0.02 * i, - WALL_HEIGHT / 2 + radius );
        glRotatef(90, 1., 0., 0.);
        glScalef(radius, radius, radius);
        drawCircleTexture(textureLife, opacity);
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);
}

void drawScore(int number, double depth) {
    double size = 0.5;
    double opacity = 1.;
    int i = 0;

    glDisable(GL_LIGHTING);

    while (number != 0) {

        int composant = number % 10;
        number /= 10;
        auto texture = getTexture("../assets/numbers/" + std::to_string(composant) + "_img.jpg");

        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(WALL_WIDTH / 2 - size - i * size, depth, -WALL_HEIGHT / 2 + size /2);
        glRotatef(90, 1., 0., 0.);
        glScalef(size, size, size);
        drawSquareTexture(texture, opacity);
        glPopMatrix();

        i++;
    }
    glEnable(GL_LIGHTING);
}