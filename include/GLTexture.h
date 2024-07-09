#pragma once
#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <glad/glad.h>

class GLTexture
{

public:

    GLTexture();

    void createTexture();

    unsigned int getID();
    unsigned int getID2();

private:

    unsigned int ID;
    unsigned int ID2;

};

#endif // !GLTEXTURE_H