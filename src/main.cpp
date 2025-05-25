#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "../include/3D_tools.hpp"
#include "../include/Ball.hpp"
#include "../include/Corridor.hpp"
#include "../include/Graphic2D.hpp"
#include "../include/Racket.hpp"
#include "../include/Collision.hpp"
#include "../include/Texture.hpp"
#include "../include/Level.hpp"
#include "../include/Light.hpp"
#include "../include/Bonus.hpp"

/* Window properties */
static const float GL_VIEW_SIZE = 6.; // Nous representons ici les points situés en -1 et 1 en x et en y

static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_filaire = 0;
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

/* Game variables */
bool inMenu = true;

double x_pos_mouse = 0;
double y_pos_mouse = 0;
double current_dept = 0.;
int scoreFinal;

Ball ball;
Racket racket;
State state = MENU_BEGIN;

int lastAction = -1;


void reset_variable() {
    inMenu = false;
    state = PLAYING;
    ball.reset();
    racket.reset();
}

/* Error handling function */
void onError(int error, const char *description) {
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

double xpos, ypos;
int s_w, s_h;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &s_w, &s_h);

    double x, y;
    if (aspectRatio > 1.0) {
        x = (-1 + 2. * xpos / (float)s_w) * aspectRatio * (GL_VIEW_SIZE / 2);
        y = ( 1 - 2. * ypos / (float)s_h) * (GL_VIEW_SIZE / 2);
    } else {
        x = (-1 + 2. * xpos / (float)s_w) * (GL_VIEW_SIZE / 2);
        y = ( 1 - 2. * ypos / (float)s_h) * (GL_VIEW_SIZE / 2) / aspectRatio;
    }
    
    x_pos_mouse = x;
    y_pos_mouse = y;
}


double x_pos_click = 0;
double y_pos_click = 0;
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    (void) button;
    (void) action;
    (void) mods;

    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &s_w, &s_h);

    double x, y;
    if (aspectRatio > 1.0) {
        x = (-1 + 2. * xpos / (float)s_w) * aspectRatio * (GL_VIEW_SIZE / 2);
        y = ( 1 - 2. * ypos / (float)s_h) * (GL_VIEW_SIZE / 2);
    } else {
        x = (-1 + 2. * xpos / (float)s_w) * (GL_VIEW_SIZE / 2);
        y = ( 1 - 2. * ypos / (float)s_h) * (GL_VIEW_SIZE / 2) / aspectRatio;
    }
    

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if(ball.isInLaunchingMode == false) {
            racket.canRacketMove = true;
        }
        lastAction = GLFW_PRESS;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        if(racket.canPress == false) {
            racket.canPress = true;
            return;
        }
        if(inMenu == false && ball.isInLaunchingMode == true) {
            ball.isInLaunchingMode = false;
            ball.canBallMove = true;
        }
        x_pos_click = x;
        y_pos_click = y;
        lastAction = GLFW_RELEASE;
        racket.canRacketMove = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        std::cout << "Mouse X = " << x << "Mouse Y = " << y << std::endl;
    }
}

void onWindowResized(GLFWwindow * /* window */, int width, int height) {
    aspectRatio = width / (float)height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    setPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
    glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int /* scancode */, int action, int /* mods */) {
    int is_pressed = (action == GLFW_PRESS);
    switch (key) {
    case GLFW_KEY_A:
    case GLFW_KEY_ESCAPE:
        if (is_pressed)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    case GLFW_KEY_F:
        if (is_pressed) {
            flag_filaire = !flag_filaire;
            std::cout << "Mode filaire : " << ((flag_filaire) ? "ON" : "OFF") << std::endl;
        }
        break;
    case GLFW_KEY_R:
        if (is_pressed)
            flag_animate_rot_arm = 1 - flag_animate_rot_arm;
        break;
    case GLFW_KEY_T:
        if (is_pressed)
            flag_animate_rot_scale = 1 - flag_animate_rot_scale;
        break;
    
    // Zoom
    case GLFW_KEY_J:
        if (dist_zoom < 60.0f)
            dist_zoom += 0.1;
        std::cout << "Zoom is " << dist_zoom << std::endl;
        break;
    case GLFW_KEY_I:
        if (dist_zoom > 1.0f)
            dist_zoom -= 0.1;
        std::cout << "Zoom is " << dist_zoom << std::endl;
        break;

    // z-near
    // case GLFW_KEY_K:
    //     Z_NEAR -= 0.1;
    //     std::cout << "Z_NEAR is " << Z_NEAR << std::endl;
    //     break;
    // case GLFW_KEY_O:
    //     Z_NEAR += 0.1;
    //     std::cout << "Z_NEAR is " << Z_NEAR << std::endl;
    //     break;

    // position camera
    case GLFW_KEY_S:
        current_dept -= 0.3;
        std::cout << "current_dept is " << current_dept << std::endl;
        break;
    case GLFW_KEY_Z:
        current_dept += 0.3;
        std::cout << "current_dept is " << current_dept << std::endl;
        break;

    case GLFW_KEY_UP:
        phy -= 2;
        std::cout << "Phy : " << phy << std::endl;
        break;
    case GLFW_KEY_DOWN:
        phy += 2;
        std::cout << "Phy : " << phy << std::endl;
        break;
    case GLFW_KEY_LEFT:
        theta -= 5;
        break;
    case GLFW_KEY_RIGHT:
        theta += 5;
        break;
    default:
        ball.pos.x = 0;
        ball.pos.y = 15;
        ball.pos.z = 0.;

        ball.dir.x = 0;
        ball.dir.y = -1;
        ball.dir.z = 0;
    }
}


double x_mouse_position;
double y_mouse_position;
int main(int /* argc */, char ** /* argv */) {
    srand(time(NULL));
    auto level = generateLevel(30);
    auto listBonus = generateBonusInLevel(rand_min_max_int(level.size() / 2, level.size()), level);
    auto copyBonus = listBonus;

    /* GLFW initialisation */
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        // If no context created : exit !
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetKeyCallback(window, onKey);
    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glfwGetCursorPos(window, &x_mouse_position, &y_mouse_position);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);

        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        // glClearColor(0.2, 0.5, 0.6, 0.0);
        glClearColor(0., 0., 0., 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (flag_filaire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if(racket.canRacketMove && !inMenu && !ball.isInLaunchingMode) {
            current_dept += racket.racket_speed;
            racket.score += racket.racket_speed;
        }
        
        glTranslatef(0, 0., current_dept);
        setCamera();
    
        if(racket.isGameFinish(level)) {
            state = MENU_WIN;
            inMenu = true;
            scoreFinal = racket.score;
            
            x_pos_click = 0;
            y_pos_click = 0;
            current_dept = 0;
            racket.reset();

            ball.canBallMove = false;
            ball.isInLaunchingMode = true;
        }

        /* 2D Scene (Menu) */
        if(inMenu) {

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            if(state == MENU_BEGIN) { drawMenu((double) GL_VIEW_SIZE); }
            if(state == MENU_WIN) { drawVictoryMenu(scoreFinal, (double) GL_VIEW_SIZE); }
            if(state == MENU_DEFEAT) { drawDefeatMenu(scoreFinal, (double) GL_VIEW_SIZE); }
            Action val = detectClick(x_pos_click, y_pos_click, state);

            switch(val) {
                case PLAY:
                case CONTINUE: // Player so he can play a new level
                    reset_variable();
                    level = generateLevel(30);
                    listBonus = generateBonusInLevel(rand_min_max_int(level.size() / 2, level.size()), level);
                    break;
                case NEWGAME:
                    reset_variable();
                    listBonus = copyBonus;
                    break;
                case QUIT:
                    exit(0);
                    break;
                case WAIT_CLICK:
                    break;
            }
        }

        /* 3D Scene rendering */
        if(!inMenu) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            
            v3d position_camera_light {racket.posMiddle.x, racket.posMiddle.y - WALL_DEPTH, racket.posMiddle.z};
            makeLight(position_camera_light, v3d {1., 1., 1.}, GL_LIGHT0);

            v3d position_ball_light {ball.pos.x + ball.radius_ball * 2, ball.pos.y, ball.pos.z + ball.radius_ball * 2};
            makeLight(position_ball_light, v3d {1., 0., 0.}, GL_LIGHT1);

            drawMultipleSection(level);
            drawAllBonus(listBonus);


            // Racket collision with wall
            bool isRacketBlocked = racket.isRacketCollideObstacle(level);
            if(isRacketBlocked) current_dept -= 0.1;
            racket.canRacketMove = !isRacketBlocked && lastAction == GLFW_PRESS;
            racket.updatePosition(x_pos_mouse, y_pos_mouse, current_dept);
            racket.drawRacket();
            drawLife(racket.posMiddle.y, racket.life);
            drawScore((int) racket.score, racket.posMiddle.y);

            if(ball.isInLaunchingMode) { // Move the mouse to launch the ball
                ball.followRacketPosition(racket);
                ball.drawBall();
                racket.isSticky = false;
            }
            if(ball.canBallMove) {  // Ball is moving in corridor
                // ball.canBallMove = false;
                // ball.isInLaunchingMode = true;

                if(ballExitCamera(ball, racket, current_dept)) { // Sort de l'écran
                    racket.life--;
                    if(racket.canRacketMove == true) {
                        racket.canPress = false;
                    }
                    if(racket.life <= 0) {
                        inMenu = true;
                        state = MENU_DEFEAT;
                        scoreFinal = racket.score;

                        x_pos_click = 0;
                        y_pos_click = 0;
                        racket.reset();
                        current_dept = 0;
                    }
                    ball.reset();
                }
                else {
                    if(ballHasTouchRacket(ball, racket)) {
                        if(racket.isSticky) {
                            ball.reset();
                            if(racket.canRacketMove) {
                                racket.canPress = false;
                            }
                        } else {
                            v3d impacte = getImpactePosition(ball, racket);
                            v3d new_dir = getNewDirection(racket, impacte);
                            drawImpact(impacte);
                            doBallBounceRacket(ball, new_dir);
                        }

                    }
                    ball.moveBall();
                    ball.drawBall();
                    
                    // Collision wall + obstacle
                    v3d normal = getNormalWhenCollide(level, ball);
                    doBallBounceWall(ball, normal);
                }
                playerGetBonus(listBonus, racket);

            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        if (elapsedTime < FRAMERATE_IN_SECONDS) {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        }
    }

    freeAllTextures();
    glfwTerminate();
    return 0;
}