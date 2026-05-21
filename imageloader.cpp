#include "imageloader.h"
#include <iostream>
#include <fstream>

using namespace std;

// Đọc 4 byte -> int 
int readInt(ifstream& f) {
    char b[4];
    f.read(b, 4);
    return (unsigned char)b[0] | ((unsigned char)b[1] << 8) | ((unsigned char)b[2] << 16) | ((unsigned char)b[3] << 24);
}

// Đọc 2 byte -> short
short readShort(ifstream& f) {
    char b[2];
    f.read(b, 2);
    return (unsigned char)b[0] | ((unsigned char)b[1] << 8);
}

unsigned char* loadBMP(const char* filename, int& width, int& height) {
    ifstream f(filename, ios::binary);
    if (!f) {
        cout << "Khong mo duoc file: " << filename << endl;
        return nullptr;
    }
    char type[2];
    f.read(type, 2);
    if (type[0] != 'B' || type[1] != 'M') {
        f.close();
        return nullptr;
    }

    f.ignore(8);
    int dataOffset = readInt(f);
    int headerSize = readInt(f);
    width = readInt(f);
    height = readInt(f);
    f.ignore(2);

    short bpp = readShort(f);
    if (bpp != 24) { 
        f.close();
        return nullptr;
    }
    f.ignore(24);

    int row_padded = (width * 3 + 3) & (~3);
    unsigned char* data = new unsigned char[width * height * 3];
    unsigned char* row = new unsigned char[row_padded];
    f.seekg(dataOffset, ios::beg);

    for (int y = 0; y < height; y++) {
        f.read((char*)row, row_padded);
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * 3;
            data[i + 0] = row[x * 3 + 2]; // R
            data[i + 1] = row[x * 3 + 1]; // G
            data[i + 2] = row[x * 3 + 0]; // B
        }
    }
    delete[] row;
    f.close();
    return data;
}

GLuint textureFromBMP(const char* filename) {
    int width, height;
    unsigned char* pixels = loadBMP(filename, width, height);
    if (pixels == nullptr) return 0;

    GLuint texHandle;
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    delete[] pixels; 
    return texHandle;
}