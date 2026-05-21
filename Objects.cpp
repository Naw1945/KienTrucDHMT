#include "Objects.h"
#include <math.h>

// Thiết lập độ sáng thủ công bằng màu sắc
void setBrightness(float& r, float& g, float& b, bool lightOn) {
    if (!lightOn) {
        r *= 0.2f; g *= 0.2f; b *= 0.2f;
    }
}

// Vẽ một hình hộp màu trơn
void drawUnitBox(float w, float h, float d, float r, float g, float b, bool lightOn) {
    glPushMatrix();
    float nr = r, ng = g, nb = b;
    setBrightness(nr, ng, nb, lightOn);
    glColor3f(nr, ng, nb);

    glBegin(GL_QUADS);
    glVertex3f(0, h, 0); glVertex3f(w, h, 0); glVertex3f(w, h, d); glVertex3f(0, h, d);
    glVertex3f(0, 0, 0); glVertex3f(0, 0, d); glVertex3f(w, 0, d); glVertex3f(w, 0, 0);
    glVertex3f(0, 0, d); glVertex3f(w, 0, d); glVertex3f(w, h, d); glVertex3f(0, h, d);
    glVertex3f(0, 0, 0); glVertex3f(0, h, 0); glVertex3f(w, h, 0); glVertex3f(w, 0, 0);
    glVertex3f(0, 0, 0); glVertex3f(0, 0, d); glVertex3f(0, h, d); glVertex3f(0, h, 0);
    glVertex3f(w, 0, 0); glVertex3f(w, h, 0); glVertex3f(w, h, d); glVertex3f(w, 0, d);
    glEnd();
    glPopMatrix();
}

// Vẽ một hình hộp có dán Texture
void drawBoxWithTexture(float w, float h, float d, GLuint texID, bool lightOn) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    if (lightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, h, 0);
    glTexCoord2f(1, 0); glVertex3f(w, h, 0);
    glTexCoord2f(1, 1); glVertex3f(w, h, d);
    glTexCoord2f(0, 1); glVertex3f(0, h, d);

    glTexCoord2f(0, 0); glVertex3f(0, 0, 0); glTexCoord2f(1, 0); glVertex3f(0, 0, d); glTexCoord2f(1, 1); glVertex3f(w, 0, d); glTexCoord2f(0, 1); glVertex3f(w, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(0, 0, d); glTexCoord2f(1, 0); glVertex3f(w, 0, d); glTexCoord2f(1, 1); glVertex3f(w, h, d); glTexCoord2f(0, 1); glVertex3f(0, h, d);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0); glTexCoord2f(1, 0); glVertex3f(0, h, 0); glTexCoord2f(1, 1); glVertex3f(w, h, 0); glTexCoord2f(0, 1); glVertex3f(w, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0); glTexCoord2f(1, 0); glVertex3f(0, 0, d); glTexCoord2f(1, 1); glVertex3f(0, h, d); glTexCoord2f(0, 1); glVertex3f(0, h, 0);
    glTexCoord2f(0, 0); glVertex3f(w, 0, 0); glTexCoord2f(1, 0); glVertex3f(w, h, 0); glTexCoord2f(1, 1); glVertex3f(w, h, d); glTexCoord2f(0, 1); glVertex3f(w, 0, d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Vẽ bàn 
void drawStudentTable(GLuint texMatBan, bool lightOn) {
    glPushMatrix();
    glTranslatef(-0.6f, 0.75f, -0.225f);
    drawBoxWithTexture(1.2f, 0.02f, 0.45f, texMatBan, lightOn);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55f, 0.71f, -0.2f);
    drawUnitBox(1.1f, 0.04f, 0.4f, 0.6f, 0.6f, 0.6f, lightOn);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-0.5f, 0.04f, -0.05f); drawUnitBox(0.06f, 0.67f, 0.1f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.44f, 0.04f, -0.05f); drawUnitBox(0.06f, 0.67f, 0.1f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.55f, 0.0f, -0.2f);  drawUnitBox(0.16f, 0.04f, 0.4f, 0.6f, 0.6f, 0.6f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.39f, 0.0f, -0.2f);   drawUnitBox(0.16f, 0.04f, 0.4f, 0.6f, 0.6f, 0.6f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.44f, 0.58f, -0.15f); drawUnitBox(0.88f, 0.015f, 0.3f, 0.65f, 0.65f, 0.65f, lightOn); glPopMatrix();
}

// Vẽ ghế 
void drawStudentChair(bool lightOn) {
    glPushMatrix();
    glTranslatef(-0.2f, 0.45f, -0.2f);
    drawUnitBox(0.4f, 0.03f, 0.4f, 0.8f, 0.55f, 0.3f, lightOn);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, 0.75f, 0.18f);
    drawUnitBox(0.4f, 0.2f, 0.03f, 0.8f, 0.55f, 0.3f, lightOn);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-0.18f, 0, -0.18f);      drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.16f, 0, -0.18f);       drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.18f, 0, 0.16f);       drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.16f, 0, 0.16f);        drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.18f, 0.45f, 0.18f); drawUnitBox(0.02f, 0.35f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.16f, 0.45f, 0.18f);  drawUnitBox(0.02f, 0.35f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
}

// Vẽ 
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

// Vẽ kết cấu thô của phòng (Sàn, Tường, Trần)
void drawRoomStructure(float W, float L, float H, GLuint texSan, GLuint texTuong, GLuint texTran) {
    glEnable(GL_TEXTURE_2D);

    // Sàn nhà
    glBindTexture(GL_TEXTURE_2D, texSan);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-W / 2, 0.0f, L / 2);
    glTexCoord2f(15.0f, 0.0f);  glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(15.0f, 15.0f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(0.0f, 15.0f);  glVertex3f(-W / 2, 0.0f, -L / 2);
    glEnd();

    // Tường bao quanh phòng
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glBegin(GL_QUADS);
    // Tường sau
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2, 0.0f, -L / 2);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(2.0f, 1.0f); glVertex3f(W / 2, H, -L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2, H, -L / 2);
    // Tường phải
    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2, 0.0f, -L / 2);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(3.0f, 1.0f); glVertex3f(W / 2, H, L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2, H, -L / 2);
    // Tường trái (Xẻ ô trống làm cửa sổ)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2, 0.0f, L / 2);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(-W / 2, 0.0f, -L / 2);
    glTexCoord2f(3.0f, 0.3f); glVertex3f(-W / 2, 0.9f, -L / 2);
    glTexCoord2f(0.0f, 0.3f); glVertex3f(-W / 2, 0.9f, L / 2);
    glTexCoord2f(0.0f, 0.7f); glVertex3f(-W / 2, H - 0.6f, L / 2);
    glTexCoord2f(3.0f, 0.7f); glVertex3f(-W / 2, H - 0.6f, -L / 2);
    glTexCoord2f(3.0f, 1.0f); glVertex3f(-W / 2, H, -L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2, H, L / 2);
    // Tường trước (Cửa ra vào)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2, 0.0f, L / 2);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, L / 2);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, H, L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2, H, L / 2);
    glTexCoord2f(0.0f, 0.8f); glVertex3f(W / 2, H - 1.0f, L / 2);
    glTexCoord2f(1.0f, 0.8f); glVertex3f(-W / 2, H - 1.0f, L / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-W / 2, H, L / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2, H, L / 2);
    glEnd();

    // Trần nhà
    glBindTexture(GL_TEXTURE_2D, texTran);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-W / 2, H, -L / 2);
    glTexCoord2f(15.0f, 0.0f);  glVertex3f(W / 2, H, -L / 2);
    glTexCoord2f(15.0f, 15.0f); glVertex3f(W / 2, H, L / 2);
    glTexCoord2f(0.0f, 15.0f);  glVertex3f(-W / 2, H, L / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// dieu hòa và đèn 
void drawCeilingAppliances(float W, float L, float H, GLuint texDieuHoa, GLuint texDen, bool lightOn) {
    float ceilingY = H - 0.001f;
    float acSize = 1.2f;
    float lightSize = 0.6f;

    glEnable(GL_TEXTURE_2D);

    // Vẽ Điều hòa
    glBindTexture(GL_TEXTURE_2D, texDieuHoa);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, L / 2 - 3.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-W / 2 + 1.8f + acSize, ceilingY, L / 2 - 3.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-W / 2 + 1.8f + acSize, ceilingY, L / 2 - 3.0f - acSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, L / 2 - 3.0f - acSize);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2 - 1.8f - acSize, ceilingY, L / 2 - 3.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(W / 2 - 1.8f, ceilingY, L / 2 - 3.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(W / 2 - 1.8f, ceilingY, L / 2 - 3.0f - acSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2 - 1.8f - acSize, ceilingY, L / 2 - 3.0f - acSize);
    glEnd();

    // Tự động chỉnh độ sáng cho Hệ thống Đèn trần
    if (lightOn) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.1f, 0.1f, 0.1f);

    // Vẽ Hệ thống Đèn
    glBindTexture(GL_TEXTURE_2D, texDen);
    glBegin(GL_QUADS);
    // Hàng đèn 1
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, L / 2 - 0.6f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-W / 2 + 1.8f + lightSize, ceilingY, L / 2 - 0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-W / 2 + 1.8f + lightSize, ceilingY, L / 2 - 0.6f - lightSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, L / 2 - 0.6f - lightSize);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-lightSize / 2, ceilingY, L / 2 - 0.6f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(lightSize / 2, ceilingY, L / 2 - 0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(lightSize / 2, ceilingY, L / 2 - 0.6f - lightSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-lightSize / 2, ceilingY, L / 2 - 0.6f - lightSize);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2 - 1.8f - lightSize, ceilingY, L / 2 - 0.6f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(W / 2 - 1.8f, ceilingY, L / 2 - 0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(W / 2 - 1.8f, ceilingY, L / 2 - 0.6f - lightSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2 - 1.8f - lightSize, ceilingY, L / 2 - 0.6f - lightSize);

    // Hàng đèn 2
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, L / 2 - 4.2f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-W / 2 + 1.8f + lightSize, ceilingY, L / 2 - 4.2f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-W / 2 + 1.8f + lightSize, ceilingY, L / 2 - 4.2f - lightSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, L / 2 - 4.2f - lightSize);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2 - 1.8f - lightSize, ceilingY, L / 2 - 4.2f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(W / 2 - 1.8f, ceilingY, L / 2 - 4.2f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(W / 2 - 1.8f, ceilingY, L / 2 - 4.2f - lightSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2 - 1.8f - lightSize, ceilingY, L / 2 - 4.2f - lightSize);

    // Hàng đèn 3
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, -L / 2 + 0.6f + lightSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-W / 2 + 1.8f + lightSize, ceilingY, -L / 2 + 0.6f + lightSize);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-W / 2 + 1.8f + lightSize, ceilingY, -L / 2 + 0.6f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-W / 2 + 1.8f, ceilingY, -L / 2 + 0.6f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-lightSize / 2, ceilingY, -L / 2 + 0.6f + lightSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(lightSize / 2, ceilingY, -L / 2 + 0.6f + lightSize);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(lightSize / 2, ceilingY, -L / 2 + 0.6f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-lightSize / 2, ceilingY, -L / 2 + 0.6f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(W / 2 - 1.8f - lightSize, ceilingY, -L / 2 + 0.6f + lightSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(W / 2 - 1.8f, ceilingY, -L / 2 + 0.6f + lightSize);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(W / 2 - 1.8f, ceilingY, -L / 2 + 0.6f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(W / 2 - 1.8f - lightSize, ceilingY, -L / 2 + 0.6f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Vẽ Bảng 
void drawBlackboard(GLuint texBang, bool lightOn) {
    glPushMatrix();
    glTranslatef(-1.5f, 1.2f, -4.45f);
    drawBoxWithTexture(3.0f, 1.2f, 0.02f, texBang, lightOn);
    glPopMatrix();
}
void drawCeilingFan(float x, float y, float z, float rotationAngle, bool lightOn) {
    glPushMatrix();
    // Di chuyển quạt đến vị trí chỉ định trên trần nhà
    glTranslatef(x, y, z);

    drawUnitBox(0.04f, 0.4f, 0.04f, 0.2f, 0.2f, 0.2f, lightOn);

    glTranslatef(0.02f, 0.0f, 0.02f);

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    float r = 0.3f, g = 0.3f, b = 0.3f; // Màu quạt mặc định
    setBrightness(r, g, b, lightOn);
    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Tâm hình tròn
    float fanRadius = 0.15f;
    for (int i = 0; i <= 30; i++) {
        float angle = i * (2.0f * 3.14159f / 30.0f);
        glVertex3f(fanRadius * cos(angle), 0.0f, fanRadius * sin(angle));
    }
    glEnd();

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);

        glTranslatef(0.15f, -0.005f, -0.06f);
        drawUnitBox(0.8f, 0.01f, 0.12f, 0.35f, 0.35f, 0.35f, lightOn);

        glPopMatrix();
    }

    glPopMatrix();
}
void drawRoomPillars(float W, float H, GLuint texTuong, bool lightOn) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texTuong);
    for (float i = -3.5f; i <= 3.5f; i += 2.0f) {
        glPushMatrix();
        glTranslatef(-W / 2, 0, i);
        drawBoxWithTexture(0.15f, H, 0.4f, texTuong, lightOn);
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
}