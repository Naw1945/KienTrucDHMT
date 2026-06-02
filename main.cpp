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

#ifndef PI
#define PI 3.14159265358979323846f
#endif

Camera cam;
bool isSpinning = false;
bool isLightOn = true;
float fanAngle = 0.0f;
bool ignoreMouseMotion = false;

TextureModel sanNha, tranThuong, tranDen, tranDieuHoa, tuongGach, bangDen;
TextureModel matBan, chanBan, chanGhe, matGhe;
TextureModel tuongPhuTrai, tuongPhuPhai, tuongPhuTren, canhCuaChinh;
TextureModel bucPhatBieu;
TextureModel oCuaSo, tuongCuaSoTren, tuongCuaSoDuoi, tuongCuaSoBien;
TextureModel quatTruc, quatBau, quatCanh;
Vector3 san_t, tran_t, bang_t;
Vector3 tuongFront_t, tuongSau_t, tuongTrai_t, tuongPhai_t;

void draw(TextureModel* m, Vector3 t);
void taoKhoiHop(TextureModel& model, const char* bmpFile, float dx, float dy, float dz);
void taoBauQuatTexture(TextureModel& model, const char* bmpFile, float banKinh, float chieuCao, int soCanh);
void drawHuongDan(float x, float y, const char* text);
void makeRoomComponents();
void veTranNha();
void veCaiBan();
void veCaiGhe();
void veQuatTran(float x, float y, float z);
void veVachTuongCoCua(float tx, float ty, float tz, float gocXoay);
void veVachTuongCoCuaSo(float tx, float ty, float tz, float gocXoay);
void renderScene(void);
void update(void);
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

void taoBauQuatTexture(TextureModel& model, const char* bmpFile, float banKinh, float chieuCao, int soCanh) {
    model.clear();
    model.setTextureFromBMP(bmpFile);

    float hMax = 0.0f;
    float hMin = -chieuCao;

    model.addVertex(point3(0.0f, hMax, 0.0f));
    model.addVertex(point3(0.0f, hMin, 0.0f));

    for (int i = 0; i < soCanh; i++) {
        float alpha = i * (2.0f * PI / soCanh);
        float x = cos(alpha) * banKinh;
        float z = sin(alpha) * banKinh;
        model.addVertex(point3(x, hMax, z));
    }

    for (int i = 0; i < soCanh; i++) {
        float alpha = i * (2.0f * PI / soCanh);
        float x = cos(alpha) * banKinh;
        float z = sin(alpha) * banKinh;
        model.addVertex(point3(x, hMin, z));
    }

    TexCoord2 tcMặcĐịnh = texCoord2(0.0f, 0.0f);

    for (int i = 0; i < soCanh; i++) {
        int next = (i + 1) % soCanh;
        int vTopHienTai = 2 + i;
        int vTopTiepTheo = 2 + next;
        int vBotHienTai = 2 + soCanh + i;
        int vBotTiepTheo = 2 + soCanh + next;

        model.addQuad(quadIndex(vTopHienTai, vBotHienTai, vBotTiepTheo, vTopTiepTheo, tcMặcĐịnh, tcMặcĐịnh, tcMặcĐịnh, tcMặcĐịnh));
        model.addTriangle(triangleIndex(0, vTopTiepTheo, vTopHienTai, tcMặcĐịnh, tcMặcĐịnh, tcMặcĐịnh));

        float alphaHienTai = i * (2.0f * PI / soCanh);
        float alphaTiepTheo = next * (2.0f * PI / soCanh);

        TexCoord2 tcCenter = texCoord2(0.5f, 0.5f);
        TexCoord2 tcHienTai = texCoord2(cos(alphaHienTai) * 0.5f + 0.5f, sin(alphaHienTai) * 0.5f + 0.5f);
        TexCoord2 tcTiepTheo = texCoord2(cos(alphaTiepTheo) * 0.5f + 0.5f, sin(alphaTiepTheo) * 0.5f + 0.5f);

        model.addTriangle(triangleIndex(1, vBotHienTai, vBotTiepTheo, tcCenter, tcHienTai, tcTiepTheo));
    }
}

void makeRoomComponents() {
    sanNha.clear();
    sanNha.setTextureFromBMP("data/sannha3.bmp");
    sanNha.addVertex(point3(-4.5f, -1.5f, 4.2f));
    sanNha.addVertex(point3(4.5f, -1.5f, 4.2f));
    sanNha.addVertex(point3(4.5f, -1.5f, -4.2f));
    sanNha.addVertex(point3(-4.5f, -1.5f, -4.2f));
    sanNha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0.5f, 14.0f), texCoord2(15.5f, 14.0f), texCoord2(15.5f, 0.0f), texCoord2(0.5f, 0.0f)));
    san_t = point3(0.0f, 0.0f, 0.0f);

    taoKhoiHop(tranThuong, "data/trannha.bmp", 0.6f, 0.01f, 0.6f);
    taoKhoiHop(tranDen, "data/den.bmp", 0.6f, 0.01f, 0.6f);
    taoKhoiHop(tranDieuHoa, "data/dieuhoa.bmp", 0.6f, 0.01f, 0.6f);

    // Khởi tạo bục phát biểu cao 1m, rộng 70cm, sâu 50cm
    taoKhoiHop(bucPhatBieu, "data/matban3.bmp", 0.7f, 1.0f, 0.5f);

    tuongGach.clear();
    tuongGach.setTextureFromBMP("data/tuong.bmp");
    tuongGach.addVertex(point3(-4.5f, -1.5f, 0.0f));
    tuongGach.addVertex(point3(4.5f, -1.5f, 0.0f));
    tuongGach.addVertex(point3(4.5f, 1.5f, 0.0f));
    tuongGach.addVertex(point3(-4.5f, 1.5f, 0.0f));
    tuongGach.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 3), texCoord2(4, 3), texCoord2(4, 0), texCoord2(0, 0)));

    taoKhoiHop(tuongPhuTrai, "data/tuong.bmp", 2.2f, 3.0f, 0.02f);
    taoKhoiHop(tuongPhuPhai, "data/tuong.bmp", 4.7f, 3.0f, 0.02f);
    taoKhoiHop(tuongPhuTren, "data/tuong.bmp", 1.5f, 0.8f, 0.02f);
    taoKhoiHop(canhCuaChinh, "data/door2.bmp", 1.5f, 2.2f, 0.01f);

    taoKhoiHop(tuongCuaSoBien, "data/tuong.bmp", 0.55f, 3.0f, 0.02f);
    taoKhoiHop(tuongCuaSoTren, "data/tuong.bmp", 7.3f, 0.7f, 0.02f);
    taoKhoiHop(tuongCuaSoDuoi, "data/tuong.bmp", 7.3f, 0.9f, 0.02f);
    taoKhoiHop(oCuaSo, "data/door2.bmp", 0.98f, 1.4f, 0.01f);

    tuongFront_t = point3(0.0f, 0.0f, -4.2f);
    tuongSau_t = point3(0.0f, 0.0f, 4.2f);
    tuongTrai_t = point3(-4.5f, 0.0f, 0.0f);
    tuongPhai_t = point3(4.5f, 0.0f, 0.0f);

    bangDen.clear();
    bangDen.setTextureFromBMP("data/bang.bmp");
    bangDen.addVertex(point3(-2.2f, -0.5f, 0.0f));
    bangDen.addVertex(point3(2.2f, -0.5f, 0.0f));
    bangDen.addVertex(point3(2.2f, 0.7f, 0.0f));
    bangDen.addVertex(point3(-2.2f, 0.7f, 0.0f));
    bangDen.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
    bang_t = point3(0.0f, 0.0f, -4.19f);

    taoKhoiHop(matBan, "data/matban3.bmp", 1.2f, 0.05f, 0.5f);
    taoKhoiHop(chanBan, "data/thanban.bmp", 0.04f, 0.7f, 0.04f);
    taoKhoiHop(matGhe, "data/matban3.bmp", 0.4f, 0.04f, 0.4f);
    taoKhoiHop(chanGhe, "data/thanban.bmp", 0.04f, 0.4f, 0.04f);

    taoKhoiHop(quatTruc, "data/thanban.bmp", 0.04f, 0.4f, 0.04f);
    taoBauQuatTexture(quatBau, "data/bauquat.bmp", 0.16f, 0.05f, 30);
    taoKhoiHop(quatCanh, "data/canhquat.bmp", 0.7f, 0.01f, 0.12f);
}

void veTranNha() {
    float size = 0.6f;

    for (int i = -8; i <= 7; i++) {
        for (int j = -7; j <= 6; j++) {
            float px = (i * size) + 0.3f;
            float pz = (j * size) + 0.3f;

            int internalX = i + 8;
            int internalY = j + 7;

            bool laDen = (internalX == 2 || internalX == 6 || internalX == 10 || internalX == 14) &&
                (internalY == 2 || internalY == 5 || internalY == 8 || internalY == 11);

            bool laDieuHoa = ((internalX == 4 && internalY == 2) || (internalX == 12 && internalY == 11));

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
    glTranslatef(-3.1f, 0.0f, 0.0f);
    tuongPhuTrai.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.85f, 0.0f, 0.0f);
    tuongPhuPhai.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25f, 1.1f, 0.0f);
    tuongPhuTren.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25f, -0.4f, 0.0f);
    canhCuaChinh.draw();
    glPopMatrix();

    glPopMatrix();
}

void veVachTuongCoCuaSo(float tx, float ty, float tz, float gocXoay) {
    glPushMatrix();
    glTranslatef(tx, ty, tz);
    glRotatef(gocXoay, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(-3.925f, 0.0f, 0.0f);
    tuongCuaSoBien.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.925f, 0.0f, 0.0f);
    tuongCuaSoBien.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 1.15f, 0.0f);
    tuongCuaSoTren.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.05f, 0.0f);
    tuongCuaSoDuoi.draw();
    glPopMatrix();

    for (int i = 0; i < 7; i++) {
        float cx = -2.94f + i * 0.98f;
        glPushMatrix();
        glTranslatef(cx, 0.1f, 0.0f);
        oCuaSo.draw();
        glPopMatrix();
    }

    glPopMatrix();
}

void veCaiBan() {
    glPushMatrix();
    glTranslatef(0.0f, -0.8f, 0.0f);
    matBan.draw();
    glPopMatrix();

    float cx[4] = { -0.55f, 0.55f, 0.55f, -0.55f };
    float cz[4] = { -0.2f, -0.2f, 0.2f, 0.2f };
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

    float cx[4] = { -0.16f, 0.16f, 0.16f, -0.16f };
    float cz[4] = { -0.16f, -0.16f, 0.16f, 0.16f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(cx[i], -1.3f, cz[i]);
        chanGhe.draw();
        glPopMatrix();
    }
}

void veQuatTran(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    quatTruc.draw();
    glPopMatrix();

    glRotatef(fanAngle, 0.0f, 1.0f, 0.0f);
    quatBau.draw();

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.42f, -0.025f, 0.0f);
        quatCanh.draw();
        glPopMatrix();
    }

    glPopMatrix();
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

    veVachTuongCoCua(tuongTrai_t.x, tuongTrai_t.y, tuongTrai_t.z, -90.0f);
    veVachTuongCoCuaSo(tuongPhai_t.x, tuongPhai_t.y, tuongPhai_t.z, -90.0f);

    veQuatTran(-1.8f, 1.3f, -1.5f);
    veQuatTran(1.8f, 1.3f, -1.5f);
    veQuatTran(-1.8f, 1.3f, 1.5f);
    veQuatTran(1.8f, 1.3f, 1.5f);

    if (isLightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);

    // Vẽ bàn giáo viên xoay ngược hướng 180 độ
    glPushMatrix();
    glTranslatef(2.2f, 0.0f, -3.2f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    veCaiBan();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.45f);
    veCaiGhe();
    glPopMatrix();
    glPopMatrix();

    // Vẽ bục phát biểu cao 1m cạnh bàn giáo viên (gần sát tường phải)
    glPushMatrix();
    glTranslatef(3.3f, -1.0f, -3.2f); // y = -1.0f giúp đáy bục đặt khít trên sàn nhà
    bucPhatBieu.draw();
    glPopMatrix();

    // Khôi phục mảng 3 cột ban đầu để giữ lại các dãy bàn ở giữa phòng
    float dãy_X[3] = { -2.3f, 0.8f, 3.9f };
    int count = 0;

    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 5; row++) {
            float zb = -1.2f + row * 0.95f;

            glPushMatrix();
            glTranslatef(dãy_X[col] - 0.6f, 0.0f, zb);
            veCaiBan();
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.45f);
            veCaiGhe();
            glPopMatrix();
            glPopMatrix();
            count++;

            if (col == 1 && row == 4) {
                continue;
            }

            // CHỈ XÓA dãy bàn ghế thò ra ngoài sát cửa sổ (col == 2 ứng với vị trí dịch phải +0.6f)
            if (col == 2) {
                continue;
            }

            glPushMatrix();
            glTranslatef(dãy_X[col] + 0.6f, 0.0f, zb);
            veCaiBan();
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.45f);
            veCaiGhe();
            glPopMatrix();
            glPopMatrix();
            count++;
        }
    }

    drawHuongDan(10, 640, "MUI TEN  : Di chuyen ");
    drawHuongDan(10, 615, "SPACE / Q: Nang / Giam do cao camera");
    drawHuongDan(10, 590, "F        : Bat / Tat quat tran");
    drawHuongDan(10, 565, "L        : Bat / tat den phong hoc");

    glutSwapBuffers();
}

void update(void) {
    if (isSpinning) {
        fanAngle += 3.0f;
        if (fanAngle > 360.0f) fanAngle -= 360.0f;
    }
    glutPostRedisplay();
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
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }

    glEnable(GL_DEPTH_TEST);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
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

    gluPerspective(70.0f, (float)width / (float)height, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    makeRoomComponents();
    glutSetCursor(GLUT_CURSOR_NONE);

    cam.x = 0.0f;
    cam.y = 0.2f;
    cam.z = 0.0f;
    cam.yaw = -90.0f;
    cam.pitch = 0.0f;
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
    glutIdleFunc(update);
    init();

    glutWarpPointer(1280 / 2, 720 / 2);
    glutMainLoop();
    return 0;
}