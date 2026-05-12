#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "imageloader.h"
#include "Camera.h"
#include "Objects.h"
#include <string>

GLuint idGachSan, idViewCanh, idMatBan, idTuong, idSky, idHell;
Camera cam;
bool firstMouse = true;
bool isSpinning = false;
bool isLightOn = true;
float chairAngle = 0.0f;
float skyHellRot = 0.0f;

const float L = 8.0f;
const float W = 6.0f;
const float H = 3.5f;

void drawUI() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    float startX = 20.0f;
    float startY = height - 30.0f;
    std::string line1 = "Nhan F de xoay ghe";
    std::string line2 = "Nhan L de bat/tat den";
    std::string line3 = "WASD / Chuot: Di chuyen camera";
    glRasterPos2f(startX, startY);
    for (char c : line1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glRasterPos2f(startX, startY - 25.0f);
    for (char c : line2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glRasterPos2f(startX, startY - 50.0f);
    for (char c : line3) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawFullCylinderBackground(float radius, float height, GLuint texSide, GLuint texTop, GLuint texBottom, float rotAngle) {
    glPushMatrix();
    glRotatef(-115.0f, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texSide);
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
    glPushMatrix();
    glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texTop);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(0, height / 2, 0);
    for (int i = 0; i <= 60; i++) {
        float angle = i * (2.0f * 3.14159f / 60.0f);
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
        glVertex3f(x, height / 2, z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texBottom);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(0, -height / 2, 0);
    for (int i = 0; i <= 60; i++) {
        float angle = i * (2.0f * 3.14159f / 60.0f);
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
        glVertex3f(x, -height / 2, z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void init() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    idGachSan = textureFromBMP("data/sannha3.bmp");
    idViewCanh = textureFromBMP("data/view1.bmp");
    idMatBan = textureFromBMP("data/matban.bmp");
    idTuong = textureFromBMP("data/tuong.bmp");
    idSky = textureFromBMP("data/sky.bmp");
    idHell = textureFromBMP("data/hell.bmp");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.apply();
    skyHellRot += 0.005f;
    if (skyHellRot > 360.0f) skyHellRot -= 360.0f;
    if (isSpinning) {
        chairAngle += 5.0f;
        if (chairAngle > 360.0f) chairAngle -= 360.0f;
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFullCylinderBackground(50.0f, 40.0f, idViewCanh, idSky, idHell, skyHellRot);
    if (isLightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idGachSan);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);    glVertex3f(-W / 2, 0.0f, L / 2);
    glTexCoord2f(10.0f, 0.0f);   glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(10.0f, 13.33f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(0.0f, 13.33f);  glVertex3f(-W / 2, 0.0f, -L / 2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, idTuong);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2, 0.0f, -L / 2);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(2.0f, 1.0f); glVertex3f(W / 2, H, -L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2, H, -L / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(3.0f, 1.0f); glVertex3f(W / 2, H, L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2, H, -L / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2, 0.0f, L / 2);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(-W / 2, 0.0f, -L / 2);
    glTexCoord2f(3.0f, 0.3f); glVertex3f(-W / 2, 0.9f, -L / 2);
    glTexCoord2f(0.0f, 0.3f); glVertex3f(-W / 2, 0.9f, L / 2);
    glTexCoord2f(0.0f, 0.7f); glVertex3f(-W / 2, H - 0.6f, L / 2);
    glTexCoord2f(3.0f, 0.7f); glVertex3f(-W / 2, H - 0.6f, -L / 2);
    glTexCoord2f(3.0f, 1.0f); glVertex3f(-W / 2, H, -L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2, H, L / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, L / 2);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, H, L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2, H, L / 2);
    glTexCoord2f(0.0f, 0.8f); glVertex3f(W / 2, H - 1.0f, L / 2);
    glTexCoord2f(1.0f, 0.8f); glVertex3f(-W / 2, H - 1.0f, L / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-W / 2, H, L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2, H, L / 2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if (isLightOn) glColor3f(1.0f, 1.0f, 0.0f);
    else glColor3f(0.2f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-W / 2, H, -L / 2); glVertex3f(W / 2, H, -L / 2);
    glVertex3f(W / 2, H, L / 2); glVertex3f(-W / 2, H, L / 2);
    glEnd();
    glPushMatrix(); glTranslatef(-1.5f, 1.2f, -3.95f); drawUnitBox(3.0f, 1.2f, 0.02f, 0.0f, 0.2f, 0.1f, isLightOn); glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTuong);
    for (float i = -3.0f; i <= 3.0f; i += 2.0f) {
        glPushMatrix(); glTranslatef(-W / 2, 0, i); drawBoxWithTexture(0.15f, H, 0.4f, idTuong, isLightOn); glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    for (float z = -1.0f; z <= 2.0f; z += 1.5f) {
        for (float x = -1.5f; x <= 1.5f; x += 3.0f) {
            glPushMatrix();
            glTranslatef(x, 0, z);
            drawStudentTable(idMatBan, isLightOn);
            glPushMatrix();
            glTranslatef(0, 0, 0.5f);
            glRotatef(chairAngle, 0.0f, 1.0f, 0.0f);
            drawStudentChair(isLightOn);
            glPopMatrix();
            glPopMatrix();
        }
    }
    drawUI();
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
    if (key == 'f' || key == 'F') isSpinning = !isSpinning;
    if (key == 'l' || key == 'L') isLightOn = !isLightOn;
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
    glutCreateWindow("Phong Hoc HAU");
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