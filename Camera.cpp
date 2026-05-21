#include "Camera.h"
#include <math.h>

// Định nghĩa hằng số chuyển đổi từ Độ sang Radian
const float TO_RAD = 3.14159265f / 180.0f;

Camera::Camera() {
    x = 0.0f; y = 1.6f; z = 5.0f;       // Chiều cao 1.6m khá chuẩn với tầm mắt người
    lx = 0.0f; ly = 0.0f; lz = -1.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    speed = 0.15f;                      // Chỉnh lại một chút cho di chuyển mượt mà, đỡ bị giật
}

void Camera::handleMouse(float xOffset, float yOffset) {
    float sensitivity = 0.1f;
    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    lx = cos(yaw * TO_RAD) * cos(pitch * TO_RAD);
    ly = sin(pitch * TO_RAD);
    lz = sin(yaw * TO_RAD) * cos(pitch * TO_RAD);
}

void Camera::handleKeyboard(unsigned char key) {
    float sgnX = cos((yaw + 90.0f) * TO_RAD);
    float sgnZ = sin((yaw + 90.0f) * TO_RAD);

    switch (key) {
    case 'w': case 'W':
        x += lx * speed;
        z += lz * speed;
        break;
    case 's': case 'S':
        x -= lx * speed;
        z -= lz * speed;
        break;
    case 'a': case 'A':
        x -= sgnX * speed;
        z -= sgnZ * speed;
        break;
    case 'd': case 'D':
        x += sgnX * speed;
        z += sgnZ * speed;
        break;
    default:
        break;
    }
}

void Camera::apply() {
    gluLookAt(x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f);
}