//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_POINT_H
#define FLAPPYTIGER_POINT_H

#include <GL/glew.h>

struct Point {
    GLfloat X;
    GLfloat Y;
    GLfloat Z;
    GLfloat UX;
    GLfloat UY;

    Point(GLfloat x, GLfloat y) {
        X = x;
        Y = y;
        Z = 0;
        UX = 0;
        UY = 0;
    }

    Point(GLfloat x, GLfloat y, GLfloat z) {
        X = x;
        Y = y;
        Z = z;
        UX = 0;
        UY = 0;
    }

    Point(GLfloat x, GLfloat y, GLfloat z, GLfloat ux, GLfloat uy) {
        X = x;
        Y = y;
        Z = z;
        UX = ux;
        UY = uy;
    }
};

#endif //FLAPPYTIGER_POINT_H
