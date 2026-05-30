#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#include "linedmodel.h"
#include "texturemodel.h"
#include "imageloader.h"
#include "Camera.h"

Camera cam;
bool isSpinning = false;
bool isLightOn = true;
float fanAngle = 0.0f;
bool ignoreMouseMotion = false;

TextureModel sanNha, tranThuong, tranDen, tranDieuHoa, tuongGach, bangDen;
TextureModel matBan, chanBan, chanGhe, matGhe, canhQuat, treoQuat, bauQuat;
TextureModel tuongPhuTrai, tuongPhuPhai, tuongPhuTren, canhCuaChinh;

Vector3 san_t, tran_t, bang_t;
Vector3 tuongFront_t, tuongSau_t, tuongTrai_t, tuongPhai_t;

void draw(TextureModel* m, Vector3 t);
void taoKhoiHop(TextureModel& model, const char* bmpFile, float dx, float dy, float dz);
void taoKhoiTruQuat(TextureModel& model, const char* bmpFile, float banKinh, float chieuCao, int soCanh);
void drawHuongDan(float x, float y, const char* text);
void makeRoomComponents();
void veTranNha();
void veCaiBan();
void veCaiGhe();
void veQuatTran(float x, float y, float z);
void veVachTuongCoCua(float tx, float ty, float tz, float gocXoay);
void renderScene(void);
void processKeys(unsigned char key, int xx, int yy);
void processSpecialKeys(int key, int xx, int yy);
void passiveMouseMotion(int mx, int my);
void resize(int width, int height);
void init();

void draw(TextureModel* m, Vector3 t) {
    glPushMatrix();
    glTranslatef(t.x, t.y, t.z);
    m->draw();
    glPopMatrix();
}

void taoKhoiHop(TextureModel& model, const char* bmpFile, float dx, float dy, float dz) {
    model.clear();
    model.setTextureFromBMP(bmpFile);

    float hx = dx / 2.0f;
    float hy = dy / 2.0f;
    float hz = dz / 2.0f;

    model.addVertex(point3(-hx, -hy, hz));
    model.addVertex(point3(hx, -hy, hz));
    model.addVertex(point3(hx, hy, hz));
    model.addVertex(point3(-hx, hy, hz));
    model.addVertex(point3(-hx, -hy, -hz));
    model.addVertex(point3(hx, -hy, -hz));
    model.addVertex(point3(hx, hy, -hz));
    model.addVertex(point3(-hx, hy, -hz));

    TexCoord2 tc0 = texCoord2(0.0f, 0.0f);
    TexCoord2 tc1 = texCoord2(1.0f, 0.0f);
    TexCoord2 tc2 = texCoord2(1.0f, 1.0f);
    TexCoord2 tc3 = texCoord2(0.0f, 1.0f);

    model.addQuad(quadIndex(0, 1, 2, 3, tc0, tc1, tc2, tc3));
    model.addQuad(quadIndex(1, 5, 6, 2, tc0, tc1, tc2, tc3));
    model.addQuad(quadIndex(5, 4, 7, 6, tc0, tc1, tc2, tc3));
    model.addQuad(quadIndex(4, 0, 3, 7, tc0, tc1, tc2, tc3));
    model.addQuad(quadIndex(3, 2, 6, 7, tc0, tc1, tc2, tc3));
    model.addQuad(quadIndex(4, 5, 1, 0, tc0, tc1, tc2, tc3));
}

void taoKhoiTruQuat(TextureModel& model, const char* bmpFile, float banKinh, float chieuCao, int soCanh) {
    model.clear();
    model.setTextureFromBMP(bmpFile);

    float hMax = chieuCao / 2.0f;
    float hMin = -chieuCao / 2.0f;

    for (int i = 0; i < soCanh; i++) {
        float alpha = i * (2 * PI / soCanh);
        float x = cos(alpha) * banKinh;
        float z = sin(alpha) * banKinh;
        model.addVertex(point3(x, hMax, z));
    }

    for (int i = 0; i < soCanh; i++) {
        float alpha = i * (2 * PI / soCanh);
        float x = cos(alpha) * banKinh;
        float z = sin(alpha) * banKinh;
        model.addVertex(point3(x, hMin, z));
    }

    TexCoord2 tc0 = texCoord2(0.0f, 0.0f);
    TexCoord2 tc1 = texCoord2(1.0f, 0.0f);
    TexCoord2 tc2 = texCoord2(1.0f, 1.0f);
    TexCoord2 tc3 = texCoord2(0.0f, 1.0f);

    for (int i = 0; i < soCanh; i++) {
        int next = (i + 1) % soCanh;
        int trenHienTai = i;
        int trenTiepTheo = next;
        int duoiHienTai = i + soCanh;
        int duoiTiepTheo = next + soCanh;
        model.addQuad(quadIndex(trenHienTai, duoiHienTai, duoiTiepTheo, trenTiepTheo, tc0, tc1, tc2, tc3));
    }
}

void makeRoomComponents() {
    float tileCount = 15.0f;

    sanNha.clear();
    sanNha.setTextureFromBMP("data/sannha3.bmp");
    sanNha.addVertex(point3(-4.5f, -1.5f, 4.5f));
    sanNha.addVertex(point3(4.5f, -1.5f, 4.5f));
    sanNha.addVertex(point3(4.5f, -1.5f, -4.5f));
    sanNha.addVertex(point3(-4.5f, -1.5f, -4.5f));
    sanNha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, tileCount), texCoord2(tileCount, tileCount), texCoord2(tileCount, 0), texCoord2(0, 0)));
    san_t = point3(0.0f, 0.0f, 0.0f);

    taoKhoiHop(tranThuong, "data/trannha.bmp", 0.6f, 0.01f, 0.6f);
    taoKhoiHop(tranDen, "data/den.bmp", 0.6f, 0.01f, 0.6f);
    taoKhoiHop(tranDieuHoa, "data/dieuhoa.bmp", 0.6f, 0.01f, 0.6f);

    tuongGach.clear();
    tuongGach.setTextureFromBMP("data/tuong.bmp");
    tuongGach.addVertex(point3(-4.5f, -1.5f, 0.0f));
    tuongGach.addVertex(point3(4.5f, -1.5f, 0.0f));
    tuongGach.addVertex(point3(4.5f, 1.5f, 0.0f));
    tuongGach.addVertex(point3(-4.5f, 1.5f, 0.0f));
    tuongGach.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 3), texCoord2(4, 3), texCoord2(4, 0), texCoord2(0, 0)));

    taoKhoiHop(tuongPhuTrai, "data/tuong.bmp", 4.0f, 3.0f, 0.02f);
    taoKhoiHop(tuongPhuPhai, "data/tuong.bmp", 3.5f, 3.0f, 0.02f);
    taoKhoiHop(tuongPhuTren, "data/tuong.bmp", 1.5f, 0.8f, 0.02f);
    taoKhoiHop(canhCuaChinh, "data/door2.bmp", 1.5f, 2.2f, 0.01f);

    tuongFront_t = point3(0.0f, 0.0f, -4.5f);
    tuongSau_t = point3(0.0f, 0.0f, 4.5f);
    tuongTrai_t = point3(-4.5f, 0.0f, 0.0f);
    tuongPhai_t = point3(4.5f, 0.0f, 0.0f);

    bangDen.clear();
    bangDen.setTextureFromBMP("data/bang.bmp");
    bangDen.addVertex(point3(-2.2f, -0.5f, 0.0f));
    bangDen.addVertex(point3(2.2f, -0.5f, 0.0f));
    bangDen.addVertex(point3(2.2f, 0.7f, 0.0f));
    bangDen.addVertex(point3(-2.2f, 0.7f, 0.0f));
    bangDen.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
    bang_t = point3(0.0f, 0.0f, -4.49f);

    taoKhoiHop(matBan, "data/matban3.bmp", 1.4f, 0.05f, 0.6f);
    taoKhoiHop(chanBan, "data/thanban.bmp", 0.04f, 0.7f, 0.04f);
    taoKhoiHop(matGhe, "data/matban3.bmp", 0.4f, 0.04f, 0.4f);
    taoKhoiHop(chanGhe, "data/thanban.bmp", 0.04f, 0.4f, 0.04f);
    taoKhoiHop(canhQuat, "data/den.bmp", 0.7f, 0.01f, 0.08f);
    taoKhoiHop(treoQuat, "data/thanban.bmp", 0.04f, 0.3f, 0.04f);
    taoKhoiTruQuat(bauQuat, "data/thanban.bmp", 0.15f, 0.075f, 30);
}

void veTranNha() {
    float size = 0.6f;

    for (int i = -7; i <= 7; i++) {
        for (int j = -7; j <= 7; j++) {
            float px = i * size;
            float pz = j * size;

            bool laDieuHoa = (i >= -1 && i <= 0) && (j >= -1 && j <= 0);
            bool laDen = ((i == -5 || i == 5) && (j == -3 || j == 3));

            glPushMatrix();
            glTranslatef(px, 1.495f, pz);

            if (laDieuHoa) {
                tranDieuHoa.draw();
            }
            else if (laDen) {
                tranDen.draw();
            }
            else {
                tranThuong.draw();
            }

            glPopMatrix();
        }
    }
}

void veVachTuongCoCua(float tx, float ty, float tz, float gocXoay) {
    glPushMatrix();
    glTranslatef(tx, ty, tz);
    glRotatef(gocXoay, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(-2.5f, 0.0f, 0.0f);
    tuongPhuTrai.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.75f, 0.0f, 0.0f);
    tuongPhuPhai.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25f, 1.1f, 0.0f);
    tuongPhuTren.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25f, -0.4f, 0.0f);
    canhCuaChinh.draw();
    glPopMatrix();

    glPopMatrix();
}

void veCaiBan() {
    glPushMatrix();
    glTranslatef(0.0f, -0.8f, 0.0f);
    matBan.draw();
    glPopMatrix();

    float cx[4] = { -0.65f, 0.65f, 0.65f, -0.65f };
    float cz[4] = { -0.25f, -0.25f, 0.25f, 0.25f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(cx[i], -1.15f, cz[i]);
        chanBan.draw();
        glPopMatrix();
    }
}

void veCaiGhe() {
    glPushMatrix();
    glTranslatef(0.0f, -1.08f, 0.0f);
    matGhe.draw();
    glPopMatrix();

    float cx[4] = { -0.18f, 0.18f, 0.18f, -0.18f };
    float cz[4] = { -0.18f, -0.18f, 0.18f, 0.18f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(cx[i], -1.3f, cz[i]);
        chanGhe.draw();
        glPopMatrix();
    }
}

// --------------------------
// New immediate-mode fan
// --------------------------
void drawUnitBox(float w, float h, float d, float r, float g, float b) {
    glColor3f(r, g, b);

    glBegin(GL_QUADS);

    // top
    glVertex3f(0, h, 0);
    glVertex3f(w, h, 0);
    glVertex3f(w, h, d);
    glVertex3f(0, h, d);

    // bottom
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, d);
    glVertex3f(w, 0, d);
    glVertex3f(w, 0, 0);

    // front
    glVertex3f(0, 0, d);
    glVertex3f(w, 0, d);
    glVertex3f(w, h, d);
    glVertex3f(0, h, d);

    // back
    glVertex3f(0, 0, 0);
    glVertex3f(0, h, 0);
    glVertex3f(w, h, 0);
    glVertex3f(w, 0, 0);

    // left
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, d);
    glVertex3f(0, h, d);
    glVertex3f(0, h, 0);

    // right
    glVertex3f(w, 0, 0);
    glVertex3f(w, h, 0);
    glVertex3f(w, h, d);
    glVertex3f(w, 0, d);

    glEnd();
}

void drawCeilingFan(float x, float y, float z, float rotationAngle) {
    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);

    glTranslatef(x, y, z);

    // trục quạt (rod) – giống vidu11_1
    drawUnitBox(0.04f, 0.4f, 0.04f, 0.6f, 0.6f, 0.6f);

    // dịch vào tâm trục rồi mới quay
    glTranslatef(0.02f, 0.0f, 0.02f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // tâm quạt (hub disc)
    // Dịch xuống để tránh Z-fighting với mặt trần
    glTranslatef(0.0f, -0.02f, 0.0f);

    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    float fanRadius = 0.15f;
    for (int i = 0; i <= 30; i++) {
        float angle = i * (2.0f * 3.14159f / 30.0f);
        glVertex3f(fanRadius * cos(angle), 0.0f, fanRadius * sin(angle));
    }
    glEnd();

    // 3 cánh quạt
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.15f, -0.005f, -0.06f);
        drawUnitBox(0.8f, 0.01f, 0.12f, 0.5f, 0.5f, 0.5f);
        glPopMatrix();
    }

    glPopAttrib();
    glPopMatrix();
}
// --------------------------
// end new fan
// --------------------------

void veQuatTran(float x, float y, float z) {
    // Thiết kế quạt theo vidu11_1: trục + tâm + 3 cánh, tất cả trong drawCeilingFan
    drawCeilingFan(x, y, z, fanAngle);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    cam.apply();

    glEnable(GL_TEXTURE_2D);

    if (isLightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);

    draw(&sanNha, san_t);
    veTranNha();

    draw(&tuongGach, tuongFront_t);
    draw(&bangDen, bang_t);

    glPushMatrix();
    glTranslatef(tuongSau_t.x, tuongSau_t.y, tuongSau_t.z);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    tuongGach.draw();
    glPopMatrix();

    veVachTuongCoCua(tuongTrai_t.x, tuongTrai_t.y, tuongTrai_t.z, 90.0f);

    glPushMatrix();
    glTranslatef(tuongPhai_t.x, tuongPhai_t.y, tuongPhai_t.z);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    tuongGach.draw();
    glPopMatrix();

    veQuatTran(0.0f, 1.3f, -1.5f);
    veQuatTran(0.0f, 1.3f, 1.5f);

    for (float zb = -1.5f; zb <= 2.5f; zb += 1.5f) {
        for (float xb = -2.5f; xb <= 2.5f; xb += 2.5f) {
            glPushMatrix();
            glTranslatef(xb, 0.0f, zb);
            veCaiBan();

            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.5f);
            veCaiGhe();
            glPopMatrix();

            glPopMatrix();
        }
    }

    if (isSpinning) {
        fanAngle += 4.0f;
        if (fanAngle > 360.0f) fanAngle -= 360.0f;
    }

    drawHuongDan(10, 690, "CHUOT    : Thay doi huong nhin");
    drawHuongDan(10, 665, "W/A/S/D  : ");
    drawHuongDan(10, 640, "MUI TEN  : Di chuyen ");
    drawHuongDan(10, 615, "SPACE / Q: Nang / Giam do cao camera");
    drawHuongDan(10, 590, "F        : Bat / Tat quat tran");
    drawHuongDan(10, 565, "L        : Bat / tat den phong hoc");

    glutSwapBuffers();
}

void drawHuongDan(float x, float y, const char* text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 720);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
    case 'f': case 'F': isSpinning = !isSpinning; break;
    case 'l': case 'L': isLightOn = !isLightOn; break;
    case 27: exit(0); break;
    default:
        cam.handleKeyboard(key);
        break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    cam.handleSpecialKeyboard(key);
    glutPostRedisplay();
}

void passiveMouseMotion(int mx, int my) {
    if (ignoreMouseMotion) {
        ignoreMouseMotion = false;
        return;
    }

    int centerX = 1280 / 2;
    int centerY = 720 / 2;

    float xOffset = (float)(mx - centerX);
    float yOffset = (float)(centerY - my);

    if (xOffset != 0 || yOffset != 0) {
        cam.handleMouse(xOffset, yOffset);
        ignoreMouseMotion = true;
        glutWarpPointer(centerX, centerY);
    }
    glutPostRedisplay();
}

void resize(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    makeRoomComponents();
    glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Mo Phong Phong Hoc HAU ");
    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(resize);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutPassiveMotionFunc(passiveMouseMotion);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    init();

    glutWarpPointer(1280 / 2, 720 / 2);
    glutMainLoop();
    return 0;
}