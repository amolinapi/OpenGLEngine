#pragma once
#ifndef GLGEOMETRY_H
#define GLGEOMETRY_H

#include "GLShader.h"

class GLGeometry
{

public:

    GLGeometry();

    static GLGeometry* instance;
    GLShader ourShader;

    unsigned int* getVBO();
    unsigned int* getVAO();
    unsigned int* getEBO();

    void createGeometry();

private:

    void geometryLogic();

    //VARIABLES
    unsigned int VBO, VAO, EBO;

    //ERROR LOG
    int success;
    char infoLog[512];
};

#endif