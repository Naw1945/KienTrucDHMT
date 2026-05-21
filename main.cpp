#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "imageloader.h"
#include "Camera.h"
#include "Objects.h"

struct RoomTextures {
    GLuint gachSan, viewCanh, matBan, tuong, sky, hell, tranNha, bang, dieuhoa, den;
} tex;

Camera cam;
bool firstMouse = true;
bool isSpinning = false;
bool isLightOn = true;
float chairAngle = 0.0f;
float skyHellRot = 0.0f;

const float ROOM_L = 9.0f;
const float ROOM_W = 9.0f;
const float ROOM_H = 3.0f;

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

    std::string lines[] = {
        "Nhan F de xoay ghe",
        "Nhan L de bat/tat den",
        "WASD / Chuot: Di chuyen camera"
    };

    for (int i = 0; i < 3; ++i) {
        glRasterPos2f(startX, startY - (i * 25.0f));
        for (char c : lines[i]) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);  glPopMatrix();
}

void updateLogic() {
    skyHellRot += 0.005f;
    if (skyHellRot > 360.0f) skyHellRot -= 360.0f;

    if (isSpinning) {
        chairAngle += 5.0f;
        if (chairAngle > 360.0f) chairAngle -= 360.0f;
    }
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    tex.gachSan = textureFromBMP("data/sannha3.bmp");
    tex.viewCanh = textureFromBMP("data/view1.bmp");
    tex.matBan = textureFromBMP("data/matban3.bmp");
    tex.tuong = textureFromBMP("data/tuong.bmp");
    tex.sky = textureFromBMP("data/sky.bmp");
    tex.hell = textureFromBMP("data/hell.bmp");
    tex.tranNha = textureFromBMP("data/trannha.bmp");
    tex.bang = textureFromBMP("data/bang.bmp");
    tex.dieuhoa = textureFromBMP("data/dieuhoa.bmp");
    tex.den = textureFromBMP("data/den.bmp");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    cam.apply();
    updateLogic();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFullCylinderBackground(50.0f, 40.0f, tex.viewCanh, tex.sky, tex.hell, skyHellRot);

    if (isLightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);

    drawRoomStructure(ROOM_W, ROOM_L, ROOM_H, tex.gachSan, tex.tuong, tex.tranNha);
    drawCeilingAppliances(ROOM_W, ROOM_L, ROOM_H, tex.dieuhoa, tex.den, isLightOn);
    drawCeilingFan(0.0f, ROOM_H - 0.45f, -1.5f, chairAngle, isLightOn);
    drawCeilingFan(0.0f, ROOM_H - 0.45f, 1.5f, chairAngle, isLightOn);
    drawBlackboard(tex.bang, isLightOn);
    drawRoomPillars(ROOM_W, ROOM_H, tex.tuong, isLightOn);

    for (float z = -1.5f; z <= 2.5f; z += 1.5f) {
        for (float x = -2.5f; x <= 2.5f; x += 2.5f) {
            glPushMatrix();
            glTranslatef(x, 0.0f, z);
            drawStudentTable(tex.matBan, isLightOn);

            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.5f);
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

    if (firstMouse) {
        glutWarpPointer(centerX, centerY);
        firstMouse = false;
        return;
    }
    if (x == centerX && y == centerY) return;

    cam.handleMouse((float)(x - centerX), (float)(centerY - y));
    glutWarpPointer(centerX, centerY);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Phím ESC
    if (key == 'f' || key == 'F') isSpinning = !isSpinning;
    if (key == 'l' || key == 'L') isLightOn = !isLightOn;

    cam.handleKeyboard(key);
    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Phong Hoc HAU - Refactored");

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