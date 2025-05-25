#include "../include/3D_tools.hpp"

/* Camera parameters and functions */
float theta = -90.0f;   // Angle between x axis and viewpoint
float phy = 90.0f;      // Angle between z axis and viewpoint
float dist_zoom = 7.8f; // Distance between origin and viewpoint

void setPerspective(float fovy, float a_ratio, float z_near, float z_far) {
    float mat[16] = {0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 0.0};
    mat[0] = 1.0;
    mat[5] = 1.0;
    mat[10] = 1.0;
    mat[15] = 1.0;

    double f = 1.0 / tanf(double(fovy) * M_PI / (360.0f)); // 1/tan(fovy/2)
    mat[0] = f / a_ratio;
    mat[5] = f;
    mat[10] = -(z_far + z_near) / (z_far - z_near);
    mat[11] = -1.0f;
    mat[14] = -2.0f * z_far * z_near / (z_far - z_near);
    mat[15] = 0.0;

    glMultMatrixf(mat);
    // gluPerspective(fovy,a_ratio,z_near,z_far);
}

void setCamera() {
    v3d eye{dist_zoom * cosf(toRad(theta)) * sinf(toRad(phy)),
            dist_zoom * sinf(toRad(theta)) * sinf(toRad(phy)),
            dist_zoom * cosf(toRad(phy))};

    // eye.display();
    v3d z_axis{cosf(toRad(theta)) * sinf(toRad(phy)),
               sinf(toRad(theta)) * sinf(toRad(phy)),
               cosf(toRad(phy))};
    z_axis.normalize();
    // z_axis.display();

    v3d up_axis{0., 0., 1.};
    v3d x_axis;
    x_axis.cross(up_axis, z_axis);
    x_axis.normalize();
    // x_axis.display();
    v3d y_axis;
    y_axis.cross(z_axis, x_axis);
    y_axis.normalize();
    // y_axis.display();

    float mat[16];
    mat[0] = x_axis.x;
    mat[4] = x_axis.y;
    mat[8] = x_axis.z;
    mat[12] = -1.0 * eye.dot(x_axis);

    mat[1] = y_axis.x;
    mat[5] = y_axis.y;
    mat[9] = y_axis.z;
    mat[13] = -1.0 * eye.dot(y_axis);

    mat[2] = z_axis.x;
    mat[6] = z_axis.y;
    mat[10] = z_axis.z;
    mat[14] = -1.0 * eye.dot(z_axis);

    mat[3] = 0.0;
    mat[7] = 0.0;
    mat[11] = 0.0;
    mat[15] = 1.0;

    glMultMatrixf(mat);
}

/* Convert degree to radians */
float toRad(float deg) {
    return deg * M_PI / 180.0f;
}

void drawSquare() {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
}

void drawCircle() {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
    for (int i = 0; i <= NB_SEG_CIRCLE; i++) {
        glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
    }
    glEnd();
}

void drawCone() {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 1.0);
    float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
    for (int i = 0; i <= NB_SEG_CIRCLE; i++) {
        glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
    }
    glEnd();
}

void drawSphere() {
    float angle_theta{0.0};
    float angle_alpha{0.0};
    float pas_angle_theta{M_PI / NB_SEG_CIRCLE};
    float pas_angle_alpha{2 * M_PI / NB_SEG_CIRCLE};
    for (int band{0}; band < NB_SEG_CIRCLE; band++) {
        angle_alpha = 0.0;
        glBegin(GL_TRIANGLE_STRIP);
        for (int count{0}; count <= NB_SEG_CIRCLE; count++) {
            glVertex3f(cosf(angle_alpha) * sinf(angle_theta),
                       sinf(angle_alpha) * sinf(angle_theta),
                       cosf(angle_theta));
            glVertex3f(cosf(angle_alpha) * sinf(angle_theta + pas_angle_theta),
                       sinf(angle_alpha) * sinf(angle_theta + pas_angle_theta),
                       cosf(angle_theta + pas_angle_theta));
            angle_alpha += pas_angle_alpha;
        }
        glEnd();
        angle_theta += pas_angle_theta;
    }
}

void drawSquareTexture(GLuint textureID, double opacity) {
    if(textureID == 0) {
        drawSquare();
        return;
    } 
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor4f(1.0, 1.0, 1.0, opacity);

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);

        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, -0.5, 0.0);

        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, -0.5, 0.0);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

// To help us with the formula, we saw this page : https://stackoverflow.com/questions/56911955/how-to-draw-texture-circle-opengl-es
// To help us with the opacity : https://www.codeproject.com/Questions/512386/TransparentplustextureplusinplusOpenGL
void drawCircleTexture(GLuint textureID, double opacity) {
    if(textureID == 0) {
        drawCircle();
        return;
    } 
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor4f(1.0, 1.0, 1.0, opacity);

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0.0, 0.0, 0.0);
        
        float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
        for (int i = 0; i <= NB_SEG_CIRCLE; i++) {
            double x = cos(i * step_rad);
            double y = sin(i * step_rad);
            double decalage = 0.9;
            double tx = 0.5 + (x * 0.5) * decalage;
            double ty = 0.5 - (y * 0.5) * decalage;
            
            glTexCoord2f(tx, ty);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

double rand_min_max_double(double min, double max) {
    return (rand() / (double)RAND_MAX) * (max - min) + min;
}

int rand_min_max_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double clamp(double value, double min, double max) {
    if(value < min) return min;
    if(value > max) return max;
    return value;
}
