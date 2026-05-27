#ifndef CAMERA_H
#define CAMERA_H

#include <glut.h>

class Camera {
public:
    float x, y, z;
    float lx, ly, lz;
    float yaw, pitch;
    float speed;

    Camera();
    void handleMouse(float xOffset, float yOffset);
    void handleKeyboard(unsigned char key);
    void handleSpecialKeyboard(int key);
    void apply();
};

#endif