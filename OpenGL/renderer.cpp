
#include "renderer.h"
#include <iostream>


void GLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLErrorLog(const char* funcName, const char* fileName, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "Error occured " << error << " at " << funcName << " in " << fileName << " in " << line << std::endl;
        return false;
    }

    return true;
}