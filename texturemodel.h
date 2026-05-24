#include <stdlib.h> // Gọi thư viện chuẩn trước
#ifndef GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK 1 // Chặn đứng GLUT định nghĩa lại exit
#endif
#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H
//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <vector>
#include "linedmodel.h"

typedef struct TexCoord2 {
	float s, t;
}TexCoord2;
TexCoord2 texCoord2(float s, float t);
typedef struct TriangleIndex {
	int A, B, C;
	TexCoord2 tcA, tcB, tcC;
}TriangleIndex;
TriangleIndex triangleIndex(int A, int B, int C, TexCoord2 tcA, TexCoord2 tcB, TexCoord2 tcC);

typedef struct QuadIndex {
	int A, B, C, D;
	TexCoord2 tcA, tcB, tcC, tcD;
}QuadIndex;
QuadIndex quadIndex(int A, int B, int C, int D, TexCoord2 tcA, TexCoord2 tcB, TexCoord2 tcC, TexCoord2 tcD);


class TextureModel {
public:
	TextureModel();
	~TextureModel();

	void setTextureFromBMP(const char* file);
	void addVertex(Point3 p);
	void addTriangle(TriangleIndex t);
	void addQuad(QuadIndex q);
	virtual void draw() const;
	void clear();
private:
	std::vector<Point3> vertices;
	std::vector<TriangleIndex> triangles;
	std::vector<QuadIndex> quads;
	GLuint texId;
};

#endif // !TEXTUREMODEL_H
#pragma once
