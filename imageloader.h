#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#define GLUT_NO_WARNING_DISABLE
#define GLUT_BUILDING_LIB

#define GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK 
#include <glut.h>

unsigned char* loadBMP(const char* filename, int& width, int& height);

GLuint textureFromBMP(const char* filename);

#endif 