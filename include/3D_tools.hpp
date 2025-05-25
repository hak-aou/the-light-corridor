#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <random>

#define NB_SEG_CIRCLE 64

/* Camera parameters and functions */
static const float Z_NEAR = 5.f;
static const float Z_FAR = 100.f;
extern float theta;     // Angle between x axis and viewpoint
extern float phy;       // Angle between z axis and viewpoint
extern float dist_zoom; // Distance between origin and viewpoint

struct v3d {
    double x{0.};
    double y{0.};
    double z{0.};

    v3d() : x(0.0), y(0.0), z(0.0) {}

    v3d(double in_x, double in_y, double in_z) : x(in_x), y(in_y), z(in_z) {}

    double length() {
        return sqrt(x * x + y * y + z * z);
    }
    void normalize() {
        double lg = this->length();
        x /= lg;
        y /= lg;
        z /= lg;
    }
    void cross(v3d b, v3d c) {
        this->x = b.y * c.z - b.z * c.y;
        this->y = c.x * b.z - c.z * b.x;
        this->z = b.x * c.y - b.y * c.x;
    }

    void display() const {
        std::cout << "V :" << x << " / " << y << " / " << z << std::endl;
    }

    double dot(v3d a) {
        return (this->x * a.x + this->y * a.y + this->z * a.z);
    }

    void vectAddition(v3d a) {
        this->x = this->x + a.x;
        this->y = this->y + a.y;
        this->z = this->z + a.z;
        this->normalize();
    }

    void vectSub(v3d a) {
        this->x = this->x - a.x;
        this->y = this->y - a.y;
        this->z = this->z - a.z;
        this->normalize();
    }

    void vectMultiplyByScalar(double n) {
        this->x = this->x * n;
        this->y = this->y * n;
        this->z = this->z * n;
        this->normalize();
    }

    v3d getDistance(v3d other) const {
        return v3d {this->x - other.x,
                    this->y - other.y,
                    this->z - other.z
                    };
    }
};

void setCamera();
void setPerspective(float fovy, float a_ratio, float z_near, float z_far);

/* Draw cannonic objet functions */
void drawSquare();

void drawCircle();

void drawCone();

void drawSphere();

/* Small tools */
float toRad(float deg);

void drawSquareTexture(GLuint textureID, double opacity);
void drawCircleTexture(GLuint textureID, double opacity);
double rand_min_max_double(double min, double max);
int rand_min_max_int(int min, int max);
double clamp(double value, double min, double max);