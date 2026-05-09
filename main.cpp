#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "imageloader.h"
#include "Camera.h"

GLuint idGachSan, idViewCanh;
Camera cam;
bool firstMouse = true;

const float L = 8.0f;
const float W = 6.0f;
const float H = 3.5f;

void drawBox(float xSize, float ySize, float zSize) {
    glPushMatrix();
    glScalef(xSize, ySize, zSize);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);   glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);   glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);  glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);   glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);  glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);   glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
    glPopMatrix();
}

void drawFullCylinderBackground(float radius, float height, GLuint texID) {
    glPushMatrix();
    glRotatef(-115.0f, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texID);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 60; i++) {
        float angle = i * (2.0f * 3.14159f / 60.0f);
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        float t = 1.0f - ((float)i / 60.0f);
        glTexCoord2f(t, 1.0f); glVertex3f(x, height / 2, z);
        glTexCoord2f(t, 0.0f); glVertex3f(x, -height / 2, z);
    }
    glEnd();
    glPopMatrix();
}

void init() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    idGachSan = textureFromBMP("data/sannha.bmp");
    idViewCanh = textureFromBMP("data/view1.bmp");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.apply();

    drawFullCylinderBackground(50.0f, 40.0f, idViewCanh);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idGachSan);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2, 0.0f, L / 2);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(4.0f, 6.0f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(0.0f, 6.0f); glVertex3f(-W / 2, 0.0f, -L / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glColor3f(0.85f, 0.85f, 0.8f);
    glPushMatrix(); glTranslatef(0, H / 2, -L / 2); drawBox(W, H, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(W / 2, H / 2, 0); drawBox(0.1f, H, L); glPopMatrix();
    glPushMatrix(); glTranslatef(-W / 2, 0.45f, 0); drawBox(0.1f, 0.9f, L); glPopMatrix();
    glPushMatrix(); glTranslatef(-W / 2, H - 0.3f, 0); drawBox(0.1f, 0.6f, L); glPopMatrix();
    for (float i = -3.0f; i <= 3.0f; i += 2.0f) {
        glPushMatrix(); glTranslatef(-W / 2, H / 2, i); drawBox(0.15f, H, 0.4f); glPopMatrix();
    }
    glPushMatrix(); glTranslatef(-W / 4, H / 2, L / 2); drawBox(W / 2, H, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(W / 4, H - 0.5f, L / 2); drawBox(W / 2, 1.0f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(W / 2, H / 2, L / 2); drawBox(0.1f, H, 0.1f); glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void mousePassiveMotion(int x, int y) {
    int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    if (firstMouse) { glutWarpPointer(centerX, centerY); firstMouse = false; return; }
    if (x == centerX && y == centerY) return;
    cam.handleMouse((float)(x - centerX), (float)(centerY - y));
    glutWarpPointer(centerX, centerY);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
    cam.handleKeyboard(key);
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Mô phỏng phòng học");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutIdleFunc(display);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();
    return 0;
}