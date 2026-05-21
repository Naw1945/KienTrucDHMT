#ifndef OBJECTS_H
#define OBJECTS_H
#define GLUT_NO_WARNING_DISABLE
#define GLUT_BUILDING_LIB

#define GLUT_DISABLE_ATEXIT_HACK
#include <glut.h>

void setBrightness(float& r, float& g, float& b, bool lightOn);
void drawUnitBox(float w, float h, float d, float r, float g, float b, bool lightOn);
void drawBoxWithTexture(float w, float h, float d, GLuint texID, bool lightOn);

void drawStudentTable(GLuint texMatBan, bool lightOn);
void drawStudentChair(bool lightOn);

void drawFullCylinderBackground(float radius, float height, GLuint texSide, GLuint texTop, GLuint texBottom, float rotAngle);
void drawRoomStructure(float W, float L, float H, GLuint texSan, GLuint texTuong, GLuint texTran);
void drawCeilingAppliances(float W, float L, float H, GLuint texDieuHoa, GLuint texDen, bool lightOn);
void drawBlackboard(GLuint texBang, bool lightOn);
void drawRoomPillars(float W, float H, GLuint texTuong, bool lightOn);
void drawCeilingFan(float x, float y, float z, float rotationAngle, bool lightOn);

#endif 