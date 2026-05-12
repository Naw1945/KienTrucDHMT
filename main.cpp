#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "imageloader.h"
#include "Camera.h"
#include "Objects.h"

GLuint idGachSan, idViewCanh, idMatBan;
Camera cam;
bool firstMouse = true;
bool isSpinning = false;
float chairAngle = 0.0f;

const float L = 8.0f;
const float W = 6.0f;
const float H = 3.5f;

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
    idGachSan = textureFromBMP("data/sannha3.bmp");
    idViewCanh = textureFromBMP("data/view1.bmp");
    idMatBan = textureFromBMP("data/matban.bmp");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.apply();

    if (isSpinning) {
        chairAngle += 5.0f;
        if (chairAngle > 360.0f) chairAngle -= 360.0f;
    }

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFullCylinderBackground(50.0f, 40.0f, idViewCanh);

    glBindTexture(GL_TEXTURE_2D, idGachSan);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);    glVertex3f(-W / 2, 0.0f, L / 2);
    glTexCoord2f(10.0f, 0.0f);   glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(10.0f, 13.33f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(0.0f, 13.33f);  glVertex3f(-W / 2, 0.0f, -L / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix(); glTranslatef(-W / 2, 0, -L / 2); drawUnitBox(W, H, 0.1f, 0.85f, 0.85f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 1.2f, -3.98f); drawUnitBox(3.0f, 1.2f, 0.02f, 0.0f, 0.2f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(W / 2, 0, -L / 2); drawUnitBox(0.1f, H, L, 0.85f, 0.85f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(-W / 2, 0, -L / 2); drawUnitBox(0.1f, 0.9f, L, 0.85f, 0.85f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(-W / 2, H - 0.6f, -L / 2); drawUnitBox(0.1f, 0.6f, L, 0.85f, 0.85f, 0.8f); glPopMatrix();
    for (float i = -3.0f; i <= 3.0f; i += 2.0f) {
        glPushMatrix(); glTranslatef(-W / 2, 0, i); drawUnitBox(0.15f, H, 0.4f, 0.85f, 0.85f, 0.8f); glPopMatrix();
    }

    glPushMatrix(); glTranslatef(-W / 2, 0, L / 2); drawUnitBox(W / 2, H, 0.1f, 0.85f, 0.85f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, H - 1.0f, L / 2); drawUnitBox(W / 2, 1.0f, 0.1f, 0.85f, 0.85f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(W / 2, 0, L / 2); drawUnitBox(0.1f, H, 0.1f, 0.85f, 0.85f, 0.8f); glPopMatrix();

    for (float z = -1.0f; z <= 2.0f; z += 1.5f) {
        for (float x = -1.5f; x <= 1.5f; x += 3.0f) {
            glPushMatrix();
            glTranslatef(x, 0, z);
            drawStudentTable(idMatBan);
            glPushMatrix();
            glTranslatef(0, 0, 0.5f);
            // Đã chỉnh: Bỏ xoay 180 độ mặc định để ghế hướng về bàn
            glRotatef(chairAngle, 0.0f, 1.0f, 0.0f);
            drawStudentChair();
            glPopMatrix();
            glPopMatrix();
        }
    }

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
    if (key == 'f' || key == 'F') isSpinning = !isSpinning;
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