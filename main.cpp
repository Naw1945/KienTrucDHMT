#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "imageloader.h"

GLuint idGachSan;
float camX = 0.0f, camY = 1.0f, camZ = 5.0f;
float lookX = 0.0f, lookY = 0.0f, lookZ = -1.0f;
float yaw = -90.0f;
float pitch = 0.0f;
float speed = 0.15f;
int lastX, lastY;
bool firstMouse = true;

void init() {
    glClearColor(0.2, 0.3, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    idGachSan = textureFromBMP("data/sannha.bmp");
    if (idGachSan == 0) {
        std::cout << "Error: Texture failed to load!" << std::endl;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ,
        camX + lookX, camY + lookY, camZ + lookZ,
        0.0, 1.0, 0.0);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, idGachSan);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-10.0f, -1.0f, -10.0f);
    glTexCoord2f(20.0f, 0.0f);  glVertex3f(10.0f, -1.0f, -10.0f);
    glTexCoord2f(20.0f, 20.0f); glVertex3f(10.0f, -1.0f, 10.0f);
    glTexCoord2f(0.0f, 20.0f);  glVertex3f(-10.0f, -1.0f, 10.0f);
    glEnd();

    glFlush();
    glutPostRedisplay();
}

void mousePassiveMotion(int x, int y) {
    if (firstMouse) {
        lastX = x; lastY = y;
        firstMouse = false;
    }

    float xOffset = x - lastX;
    float yOffset = lastY - y;
    lastX = x; lastY = y;

    float sensitivity = 0.15f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    lookX = cos(yaw * 3.14159 / 180.0) * cos(pitch * 3.14159 / 180.0);
    lookY = sin(pitch * 3.14159 / 180.0);
    lookZ = sin(yaw * 3.14159 / 180.0) * cos(pitch * 3.14159 / 180.0);
}

void keyboard(unsigned char key, int x, int y) {
    float dx = lookX * speed;
    float dz = lookZ * speed;

    switch (key) {
    case 'w': camX += dx; camZ += dz; break;
    case 's': camX -= dx; camZ -= dz; break;
    case 'a': camX += dz; camZ -= dx; break;
    case 'd': camX -= dz; camZ += dx; break;
    case 27:  exit(0); break;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Phong Hoc 3D ");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mousePassiveMotion);

    glutSetCursor(GLUT_CURSOR_NONE);

    glutMainLoop();
    return 0;
}