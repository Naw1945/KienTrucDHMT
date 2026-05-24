#include <stdlib.h> // Gọi thư viện chuẩn trước
#ifndef GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK 1 // Chặn đứng GLUT định nghĩa lại exit
#endif
#ifndef MODEL_H
#define MODEL_H
//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
#include <math.h>

#define MAX_VERTICES 10000
#define MAX_LINES 10000
#define PI 3.14159265
//#define PI 3.14
typedef struct Point3 {
	double x, y, z;
}Point3;
typedef Point3 Vector3;

typedef struct LinedModel {
	int nVertices; // số lượng đỉnh
	Point3 vertices[MAX_VERTICES]; // danh sách các đỉnh
	int nEdges; // số lượng cạnh
	int edges[MAX_LINES][2]; // danh sách các cạnh
}LinedModel;

void drawLinedModel(LinedModel* m);
void regularPolygon(LinedModel* m, double r, int n);

Point3 point3(double x, double y, double z);
void drawLinedModel(LinedModel* m, Vector3 v);
void regularPolygon(LinedModel* m, int n, double A0x, double A0y);
void regularPolygon1(LinedModel* m, double r, int n, double startAngle);


#endif // !MODEL_H
#pragma once
