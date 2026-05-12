#ifndef OBJECTS_H
#define OBJECTS_H

#include <glut.h>
void setBrightness(float& r, float& g, float& b, bool lightOn) {
    if (!lightOn) {
        r *= 0.2f;
        g *= 0.2f;
        b *= 0.2f;
    }
}

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
    
    glVertex3f(0, 0, 0); glVertex3f(0, 0, d); glVertex3f(w, 0, d); glVertex3f(w, 0, 0);
    glVertex3f(0, 0, d); glVertex3f(w, 0, d); glVertex3f(w, h, d); glVertex3f(0, h, d);
    glVertex3f(0, 0, 0); glVertex3f(0, h, 0); glVertex3f(w, h, 0); glVertex3f(w, 0, 0);
    glVertex3f(0, 0, 0); glVertex3f(0, 0, d); glVertex3f(0, h, d); glVertex3f(0, h, 0);
    glVertex3f(w, 0, 0); glVertex3f(w, h, 0); glVertex3f(w, h, d); glVertex3f(w, 0, d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

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
    glPushMatrix(); glTranslatef(-0.55f, 0.0f, -0.2f); drawUnitBox(0.16f, 0.04f, 0.4f, 0.6f, 0.6f, 0.6f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.39f, 0.0f, -0.2f); drawUnitBox(0.16f, 0.04f, 0.4f, 0.6f, 0.6f, 0.6f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.44f, 0.58f, -0.15f); drawUnitBox(0.88f, 0.015f, 0.3f, 0.65f, 0.65f, 0.65f, lightOn); glPopMatrix();
}

void drawStudentChair(bool lightOn) {
    glPushMatrix();
    glTranslatef(-0.2f, 0.45f, -0.2f);
    drawUnitBox(0.4f, 0.03f, 0.4f, 0.8f, 0.55f, 0.3f, lightOn);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, 0.75f, 0.18f);
    drawUnitBox(0.4f, 0.2f, 0.03f, 0.8f, 0.55f, 0.3f, lightOn);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-0.18f, 0, -0.18f); drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.16f, 0, -0.18f);  drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.18f, 0, 0.16f);  drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.16f, 0, 0.16f);   drawUnitBox(0.02f, 0.45f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.18f, 0.45f, 0.18f); drawUnitBox(0.02f, 0.35f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
    glPushMatrix(); glTranslatef(0.16f, 0.45f, 0.18f);  drawUnitBox(0.02f, 0.35f, 0.02f, 0.7f, 0.7f, 0.7f, lightOn); glPopMatrix();
}

#endif