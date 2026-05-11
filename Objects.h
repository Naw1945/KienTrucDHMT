#ifndef OBJECTS_H
#define OBJECTS_H

#include <glut.h>

void drawUnitBox(float w, float h, float d, float r, float g, float b) {
    glPushMatrix();
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(0, h, 0); glVertex3f(w, h, 0);
    glVertex3f(w, h, d); glVertex3f(0, h, d);
    glVertex3f(0, 0, 0); glVertex3f(0, 0, d);
    glVertex3f(w, 0, d); glVertex3f(w, 0, 0);
    glVertex3f(0, 0, d); glVertex3f(w, 0, d);
    glVertex3f(w, h, d); glVertex3f(0, h, d);
    glVertex3f(0, 0, 0); glVertex3f(0, h, 0);
    glVertex3f(w, h, 0); glVertex3f(w, 0, 0);
    glVertex3f(0, 0, 0); glVertex3f(0, 0, d);
    glVertex3f(0, h, d); glVertex3f(0, h, 0);
    glVertex3f(w, 0, 0); glVertex3f(w, h, 0);
    glVertex3f(w, h, d); glVertex3f(w, 0, d);
    glEnd();
    glPopMatrix();
}

void drawStudentTable() {
    glPushMatrix();
    glTranslatef(-0.6f, 0.7f, -0.3f);
    drawUnitBox(1.2f, 0.05f, 0.6f, 0.5f, 0.35f, 0.05f);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-0.55f, 0, -0.25f); drawUnitBox(0.05f, 0.7f, 0.05f, 0.2f, 0.2f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.50f, 0, -0.25f);  drawUnitBox(0.05f, 0.7f, 0.05f, 0.2f, 0.2f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.55f, 0, 0.20f);  drawUnitBox(0.05f, 0.7f, 0.05f, 0.2f, 0.2f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.50f, 0, 0.20f);   drawUnitBox(0.05f, 0.7f, 0.05f, 0.2f, 0.2f, 0.2f); glPopMatrix();
}

void drawStudentChair() {
    glPushMatrix();
    glTranslatef(-0.2f, 0.4f, -0.2f);
    drawUnitBox(0.4f, 0.04f, 0.4f, 0.4f, 0.25f, 0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, 0.44f, -0.2f);
    drawUnitBox(0.4f, 0.4f, 0.04f, 0.4f, 0.25f, 0.05f);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-0.18f, 0, -0.18f); drawUnitBox(0.03f, 0.4f, 0.03f, 0.1f, 0.1f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.15f, 0, -0.18f);  drawUnitBox(0.03f, 0.4f, 0.03f, 0.1f, 0.1f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.18f, 0, 0.15f);  drawUnitBox(0.03f, 0.4f, 0.03f, 0.1f, 0.1f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.15f, 0, 0.15f);   drawUnitBox(0.03f, 0.4f, 0.03f, 0.1f, 0.1f, 0.1f); glPopMatrix();
}

#endif