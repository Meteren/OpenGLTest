#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();

#define CALL(x) GLClearErrors();\
    x;\
    ASSERT(GLErrorLog(#x,__FILE__, __LINE__));


void GLClearErrors();
   

bool GLErrorLog(const char* funcName, const char* fileName, int line);