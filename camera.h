#ifndef CAMERA_H
#define CAMERA_H

#include <glut.h>
#include <math.h>

class Camera {
public:
    float x, y, z;          
    float lx, ly, lz;       
    float yaw, pitch;
    float speed;

    Camera() {
        x = 0.0f; y = 1.6f; z = 5.0f;
        lx = 0.0f; ly = 0.0f; lz = -1.0f;
        yaw = -90.0f;
        pitch = 0.0f;
        speed = 0.2f;
    }

    void handleMouse(int xOffset, int yOffset) {
        float sensitivity = 0.1f;
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        lx = cos(yaw * 3.14159 / 180.0) * cos(pitch * 3.14159 / 180.0);
        ly = sin(pitch * 3.14159 / 180.0);
        lz = sin(yaw * 3.14159 / 180.0) * cos(pitch * 3.14159 / 180.0);
    }

    void handleKeyboard(unsigned char key) {
        float sgnX = cos((yaw + 90) * 3.14159 / 180.0);
        float sgnZ = sin((yaw + 90) * 3.14159 / 180.0);

        switch (key) {
        case 'w': x += lx * speed; z += lz * speed; break;
        case 's': x -= lx * speed; z -= lz * speed; break;
        case 'a': x -= sgnX * speed; z -= sgnZ * speed; break;
        case 'd': x += sgnX * speed; z += sgnZ * speed; break;
        }
    }

    void apply() {
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
    }
};

#endif#pragma once
