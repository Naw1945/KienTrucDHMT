#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#include "linedmodel.h"
#include "texturemodel.h"
#include "imageloader.h"

// --- BIẾN TRẠNG THÁI & HỆ GÓC NHÌN ---
float lx = 0.0f, lz = 0.0f;
float x = 0.0f, z = 5.0f;
float angle = -1.5f;
float speed = 0.1f;
float heightAngle = 0.0f;
float height_view = -1.0f;
float cameraY = 1.0f;

bool isSpinning = false;
bool isLightOn = true;
float fanAngle = 0.0f;

// --- KHAI BÁO MÔ HÌNH VẬT THỂ ---
TextureModel sanNha, tranThuong, tranDen, tranDieuHoa, tuongGach, tuongCua, bangDen;
TextureModel matBan, chanBan, chanGhe, matGhe, canhQuat, treoQuat;

Vector3 san_t, tran_t, bang_t;
Vector3 tuongTruoc_t, tuongSau_t, tuongTrai_t, tuongPhai_t;

// --- KHAI BÁO HÀM ---
void draw(TextureModel* m, Vector3 t);
void taoKhoiHop(TextureModel& model, const char* bmpFile, float dx, float dy, float dz);
void drawHuongDan(float x, float y, const char* text);
void makeRoomComponents();
void veTranNha();
void veCaiBan();
void veCaiGhe();
void veQuatTran(float x, float y, float z);
void renderScene(void);
void processKeys(unsigned char key, int xx, int yy);
void processSpecialKeys(int key, int xx, int yy);
void resize(int width, int height);
void init();

// --- HÀM VẼ CO LẬP MA TRẬN ---
void draw(TextureModel* m, Vector3 t) {
    glPushMatrix();
    glTranslatef(t.x, t.y, t.z);
    m->draw();
    glPopMatrix();
}

// --- HÀM KHỞI TẠO KHỐI HỘP DÁN TEXTURE ---
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

// --- KHỞI TẠO VẬT THỂ PHÒNG HỌC ---
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

    tuongCua.clear();
    tuongCua.setTextureFromBMP("data/tuong.bmp");
    tuongCua.addVertex(point3(-4.5f, -1.5f, 0.0f));
    tuongCua.addVertex(point3(4.5f, -1.5f, 0.0f));
    tuongCua.addVertex(point3(4.5f, 1.5f, 0.0f));
    tuongCua.addVertex(point3(-4.5f, 1.5f, 0.0f));
    tuongCua.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

    tuongTruoc_t = point3(0.0f, 0.0f, -4.5f);
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
    taoKhoiHop(treoQuat, "data/thanban.bmp", 0.04f, 0.4f, 0.04f);
}

// --- HÀM VẼ HỆ THỐNG TRẦN Ô MA TRẬN ---
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

// --- CÁC HÀM VẼ NỘI THẤT ---
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

void veQuatTran(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, 1.4f, z);
    treoQuat.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(fanAngle, 0.0f, 1.0f, 0.0f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.35f, -0.1f, 0.0f);
        canhQuat.draw();
        glPopMatrix();
    }
    glPopMatrix();
}

// --- HÀM HIỂN THỊ CHÍNH ---
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(x, cameraY, z,
        x + lx, cameraY + sin(heightAngle), z + lz,
        0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);

    if (isLightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);

    draw(&sanNha, san_t);
    veTranNha();

    draw(&tuongGach, tuongTruoc_t);
    draw(&bangDen, bang_t);

    glPushMatrix(); glTranslatef(tuongSau_t.x, tuongSau_t.y, tuongSau_t.z); glRotatef(180, 0, 1, 0); tuongCua.draw(); glPopMatrix();
    glPushMatrix(); glTranslatef(tuongTrai_t.x, tuongTrai_t.y, tuongTrai_t.z); glRotatef(90, 0, 1, 0); tuongCua.draw(); glPopMatrix();
    glPushMatrix(); glTranslatef(tuongPhai_t.x, tuongPhai_t.y, tuongPhai_t.z); glRotatef(-90, 0, 1, 0); tuongGach.draw(); glPopMatrix();

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

    drawHuongDan(10, 690, "W / S    : Tang / Giam do cao goc nhin");
    drawHuongDan(10, 665, "A / D    : Quay trai / phai camera");
    drawHuongDan(10, 640, "SPACE / Q: Tang / Giam do cao cua camera");
    drawHuongDan(10, 615, "F        : Bat / Tat quay quat tran");
    drawHuongDan(10, 590, "L        : Bat / Tat thap sang phong hoc");
    drawHuongDan(10, 565, "ESC      : Thoat ung dung");

    glutSwapBuffers();
}

// --- HÀM VẼ CHỮ HƯỚNG DẪN 2D ---
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

// --- XỬ LÝ SỰ KIỆN BÀN PHÍM ---
void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
    case 'f': case 'F': isSpinning = !isSpinning; break;
    case 'l': case 'L': isLightOn = !isLightOn; break;
    case 'w':
        if (heightAngle < PI / 2) { heightAngle += 0.05f; height_view = sin(heightAngle); }
        break;
    case 's':
        if (heightAngle > (-PI / 2)) { heightAngle -= 0.05f; height_view = sin(heightAngle) - 1.0f; }
        break;
    case 'a':
        angle -= 0.03f; lx = cos(angle); lz = sin(angle);
        break;
    case 'd':
        angle += 0.03f; lx = cos(angle); lz = sin(angle);
        break;
    case ' ':
        cameraY += 0.1f;
        break;
    case 'q':
        cameraY -= 0.1f;
        break;
    case 27: exit(0);
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    float fraction = speed;
    switch (key) {
    case GLUT_KEY_LEFT:  x += lz * fraction; z -= lx * fraction; break;
    case GLUT_KEY_RIGHT: x -= lz * fraction; z += lx * fraction; break;
    case GLUT_KEY_UP:    x += lx * fraction; z += lz * fraction; break;
    case GLUT_KEY_DOWN:  x -= lx * fraction; z -= lz * fraction; break;
    }
    glutPostRedisplay();
}

// --- KHỞI TẠO HỆ THỐNG CỬA SỔ VÀ ĐỒ HỌA ---
void resize(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    lx = cos(angle);
    lz = sin(angle);
    makeRoomComponents();
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
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    init();

    glutMainLoop();
    return 0;
}