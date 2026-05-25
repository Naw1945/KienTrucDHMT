#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#include "linedmodel.h"
#include "texturemodel.h"
#include "imageloader.h"
void drawHuongDan(float x, float y, const char* text);

// --- Đồng bộ hóa biến Camera & Di chuyển chuẩn theo Vidu11 ---
float lx = 0.0f, lz = 0.0f;
float x = 0.0f, z = 5.0f; // Đứng ở z=5 để nhìn vào phòng học
float angle = -1.5f;       // Hướng nhìn mặc định ban đầu
float speed = 0.1f;
float heightAngle = 0.0f;
float height_view = -1.0f; // Độ cao góc nhìn mặc định
float cameraY = 1.0f; // Độ cao của camera (đứng trên mặt đất)

// --- Trạng thái logic phòng học từ bản cũ của bạn ---
bool isSpinning = false;
bool isLightOn = true;
float chairAngle = 0.0f;

// --- Khai báo TextureModel theo cấu trúc của thầy ---
TextureModel sanNha, tranNha, tuongGach, bangDen, matBan, chanBanGhe, matGhe, canhQuat;
Vector3 san_t, tran_t, tuongTruoc_t, tuongSau_t, tuongTrai_t, tuongPhai_t, bang_t;

// --- Hàm draw chuẩn mẫu của thầy Toản trong Vidu11 ---
void draw(TextureModel* m, Vector3 t) {
    glPushMatrix();
    glTranslatef(t.x, t.y, t.z);
    m->draw();
    glPopMatrix();
}

// --- Hàm bổ trợ tạo khối hộp dán texture chuẩn chỉ xung quanh gốc (0,0,0) ---
void taoKhoiHop(TextureModel& model, const char* bmpFile, float dx, float dy, float dz) {
    model.clear();
    model.setTextureFromBMP(bmpFile);

    float hx = dx / 2.0f;
    float hy = dy / 2.0f;
    float hz = dz / 2.0f;

    model.addVertex(point3(-hx, -hy, hz)); // 0
    model.addVertex(point3(hx, -hy, hz)); // 1
    model.addVertex(point3(hx, hy, hz)); // 2
    model.addVertex(point3(-hx, hy, hz)); // 3
    model.addVertex(point3(-hx, -hy, -hz)); // 4
    model.addVertex(point3(hx, -hy, -hz)); // 5
    model.addVertex(point3(hx, hy, -hz)); // 6
    model.addVertex(point3(-hx, hy, -hz)); // 7

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

// --- Các hàm khởi tạo vật thể độc lập ---
void makeRoomComponents() {
    // Kích thước phòng 9x9x3 gạch sàn 60x60cm => Tiling hệ số 15
    float tileCount = 15.0f;

    // Thiết lập Sàn nằm phẳng tại gốc tọa độ
    sanNha.clear(); sanNha.setTextureFromBMP("data/sannha3.bmp");
    sanNha.addVertex(point3(-4.5, -1.5, 4.5)); // Đẩy sàn xuống y = -1.5 tương đương góc nhìn thầy
    sanNha.addVertex(point3(4.5, -1.5, 4.5));
    sanNha.addVertex(point3(4.5, -1.5, -4.5));
    sanNha.addVertex(point3(-4.5, -1.5, -4.5));
    sanNha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, tileCount), texCoord2(tileCount, tileCount), texCoord2(tileCount, 0), texCoord2(0, 0)));
    san_t = point3(0, 0, 0);

    // Thiết lập Trần nhà tại độ cao y = 1.5 (Tổng độ cao phòng là 3.0m)
    tranNha.clear(); tranNha.setTextureFromBMP("data/trannha.bmp");
    tranNha.addVertex(point3(-4.5, 1.5, -4.5));
    tranNha.addVertex(point3(4.5, 1.5, -4.5));
    tranNha.addVertex(point3(4.5, 1.5, 4.5));
    tranNha.addVertex(point3(-4.5, 1.5, 4.5));
    tranNha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, tileCount), texCoord2(tileCount, tileCount), texCoord2(tileCount, 0), texCoord2(0, 0)));
    tran_t = point3(0, 0, 0);

    // Bức tường phẳng chung (Rộng 9m, Cao 3m)
    tuongGach.clear(); tuongGach.setTextureFromBMP("data/tuong.bmp");
    tuongGach.addVertex(point3(-4.5, -1.5, 0));
    tuongGach.addVertex(point3(4.5, -1.5, 0));
    tuongGach.addVertex(point3(4.5, 1.5, 0));
    tuongGach.addVertex(point3(-4.5, 1.5, 0));
    tuongGach.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 3), texCoord2(4, 3), texCoord2(4, 0), texCoord2(0, 0)));

    // Vị trí tịnh tiến cho 4 bức tường bao quanh phòng học 9x9
    tuongTruoc_t = point3(0, 0, -4.5);
    tuongSau_t = point3(0, 0, 4.5);
    tuongTrai_t = point3(-4.5, 0, 0);
    tuongPhai_t = point3(4.5, 0, 0);

    // Bảng viết căn giữa
    bangDen.clear(); bangDen.setTextureFromBMP("data/bang.bmp");
    bangDen.addVertex(point3(-2.2f, -0.5f, 0));
    bangDen.addVertex(point3(2.2f, -0.5f, 0));
    bangDen.addVertex(point3(2.2f, 0.7f, 0));
    bangDen.addVertex(point3(-2.2f, 0.7f, 0));
    bangDen.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
    bang_t = point3(0, 0, -4.49f); // Đặt sát tường trước

    // Khởi tạo các hình khối nhỏ cho nội thất bàn ghế
    taoKhoiHop(matBan, "data/matban3.bmp", 1.4f, 0.05f, 0.6f);
    taoKhoiHop(chanBanGhe, "data/tuong.bmp", 0.04f, 0.7f, 0.04f);
    taoKhoiHop(matGhe, "data/matban3.bmp", 0.4f, 0.04f, 0.4f);
    taoKhoiHop(canhQuat, "data/den.bmp", 0.7f, 0.01f, 0.08f);
}

void veCaiBan() {
    glPushMatrix(); glTranslatef(0.0f, -0.8f, 0.0f); matBan.draw(); glPopMatrix();
    float cx[4] = { -0.65f, 0.65f, 0.65f, -0.65f };
    float cz[4] = { -0.25f, -0.25f, 0.25f, 0.25f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(cx[i], -1.15f, cz[i]);
        chanBanGhe.draw();
        glPopMatrix();
    }
}

void veCaiGhe() {
    glPushMatrix(); glTranslatef(0.0f, -1.05f, 0.0f); matGhe.draw(); glPopMatrix();
    float cx[4] = { -0.18f, 0.18f, 0.18f, -0.18f };
    float cz[4] = { -0.18f, -0.18f, 0.18f, 0.18f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(cx[i], -1.275f, cz[i]);
        chanBanGhe.draw();
        glPopMatrix();
    }
}

void veQuatTran(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(chairAngle, 0.0f, 1.0f, 0.0f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.35f, 0.0f, 0.0f);
        canhQuat.draw();
        glPopMatrix();
    }
    glPopMatrix();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Hệ góc nhìn gluLookAt đồng bộ hoàn toàn với Vidu11 của thầy
    gluLookAt(x, cameraY, z,
        x + lx, cameraY + height_view, z + lz,
        0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);

    if (isLightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);

    // Vẽ vỏ phòng học sử dụng hàm draw() con trỏ mẫu của thầy
    draw(&sanNha, san_t);
    draw(&tranNha, tran_t);
    draw(&tuongGach, tuongTruoc_t);
    draw(&bangDen, bang_t);

    // Tường sau và hai bên cần góc xoay tương ứng để khép kín hộp 3D
    glPushMatrix(); glTranslatef(tuongSau_t.x, tuongSau_t.y, tuongSau_t.z); glRotatef(180, 0, 1, 0); tuongGach.draw(); glPopMatrix();
    glPushMatrix(); glTranslatef(tuongTrai_t.x, tuongTrai_t.y, tuongTrai_t.z); glRotatef(90, 0, 1, 0); tuongGach.draw(); glPopMatrix();
    glPushMatrix(); glTranslatef(tuongPhai_t.x, tuongPhai_t.y, tuongPhai_t.z); glRotatef(-90, 0, 1, 0); tuongGach.draw(); glPopMatrix();

    // Thiết bị trần nhà
    veQuatTran(0.0f, 1.3f, -1.5f);
    veQuatTran(0.0f, 1.3f, 1.5f);

    // Ma trận cụm bàn ghế học sinh
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
        chairAngle += 4.0f;
        if (chairAngle > 360.0f) chairAngle -= 360.0f;
    }
	drawHuongDan(10, 690, "W/S: Tang/Giam do cao goc nhin | A/D: Quay trai/phai | F: Bat/Tat quay | L: Bat/Tat den | Space/Q: Tang/Giam do cao camera | ESC: Thoat");
    glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
    case 'f': case 'F': isSpinning = !isSpinning; break;
    case 'l': case 'L': isLightOn = !isLightOn; break;
    case 'w':
        if (heightAngle < PI / 2) { heightAngle += 0.05f; height_view = sin(heightAngle) - 1.0f; }
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
    case ' ': // Space để reset góc nhìn về mặc định
        cameraY += 0.1f;
		break;
    case 'q':
        cameraY -= 0.1f;
		break;
    case 27: exit(0);
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