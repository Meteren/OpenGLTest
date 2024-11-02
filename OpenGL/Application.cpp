#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

#include <sstream>

#include "renderer.h"

#include "vertexBuffer.h"

#include "IndexBuffer.h"

struct ShaderSource {
    std::string Vertex;
    std::string Fragment;
};

static ShaderSource ParseShader(const std::string filePath) {
    std::fstream stream(filePath);

    enum class Type {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    Type type = Type::NONE;

    std::stringstream str[2];

    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = Type::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = Type::FRAGMENT;
        }
        else
        {
            str[(int)type] << line << std::endl;
            
        }
    }

    ShaderSource shaderSource{
       str[0].str(),str[1].str()
    };

    return shaderSource;
}


static unsigned int CompileShader(unsigned int type, std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* srcPtr = source.c_str();
    glShaderSource(id, 1, &srcPtr,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)_malloca(sizeof(char) * lenght);
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << message << std::endl;
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex shader issue" : "Fragment shader issue") << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


static unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float data[8] = {
             -0.5,-0.5,
             0.5, -0.5,
             0.5, 0.5,
             -0.5,0.5
        };

        unsigned int indices[6] = {
            0,1,2,
            2,3,0
        };

        VertexBuffer vertexBuffer(data, 4 * 2 * sizeof(float));

        IndexBuffer indexBuffer(indices, 6);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        ShaderSource shaderSource = ParseShader("basic.shader");

        unsigned int program = CreateShader(shaderSource.Vertex, shaderSource.Fragment);

        glUseProgram(program);

        CALL(int location = glGetUniformLocation(program, "u_Color"));

        float r = 0.05f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glUniform4f(location, r, 0.3, 0.2, 1.0);
            CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(program);
    }
    glfwTerminate();
    return 0;
}