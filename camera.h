#ifndef CAMERA_H
#define CAMERA_H
#define GLUT_NO_WARNING_DISABLE
#define GLUT_BUILDING_LIB

#define GLUT_DISABLE_ATEXIT_HACK
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

    void apply();
};

#endif 