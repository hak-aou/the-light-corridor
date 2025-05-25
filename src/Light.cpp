#include "../include/Light.hpp"

void makeLight(v3d positionVector, v3d color, GLenum numLight) {
    float position[4] = {(float) positionVector.x, (float) positionVector.y, (float) positionVector.z, 1.0};
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glPopMatrix();
    
    GLfloat view[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, view);

    float overall_intensity = 400.0;
    float black[4] = {0.0, 0.0, 0.0, 1.0};
    float spec_intensity[4] = {overall_intensity, 0.0, 0.0, 0.0};
    float intensite[4] = {(float) color.x * overall_intensity,
                          (float) color.y * overall_intensity,
                          (float) color.z * overall_intensity, 0.0};
   
    glEnable(GL_LIGHTING);
    glEnable(numLight);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightfv(numLight, GL_POSITION, position);
    glLightfv(numLight, GL_AMBIENT, black);
    glLightfv(numLight, GL_DIFFUSE, intensite);
    glLightfv(numLight, GL_SPECULAR, spec_intensity);
    glLightf(numLight, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(numLight, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(numLight, GL_QUADRATIC_ATTENUATION, MY_PI);
}