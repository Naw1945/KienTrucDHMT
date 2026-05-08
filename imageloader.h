#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <stdlib.h>              
#define GLUT_DISABLE_ATEXIT_HACK 
#include <glut.h>
#include <stddef.h>              

unsigned char* loadBMP(const char* filename, int& width, int& height);
GLuint textureFromBMP(const char* filename);

#endif