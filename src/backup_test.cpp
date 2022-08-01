// include libraries
#include <iostream>
#include <string.h>

#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "opengl_utils.h"

// namespaces
using namespace std;

// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// VAO and VBO of triangles
GLuint triangle_VAO, triangle_VBO;

// triangle program
GLuint triangle_program;

// triangle uniform model address
GLuint triangle_uniformModel;

// triangle moving animation values
bool triangle_direction = true;
float triangle_offset = 0.0f;
float triangle_maxOffset = 0.7f;
float triangle_increment = 0.005f;

// triangle scaling animation values
bool triangle_scaleDir = true;
float triangle_curSize = 0.01f;
float triangle_incrSize = 0.0008f;
float triangle_maxSize = 0.03f;
float triangle_minSize = 0.0f;

// triangle rotating animation values
float triangle_curAngle = 0.0f;
float triangle_incrAngle = 65.0f;

// vertex shader
static const char* triangle_vShader = "                      \n\
#version 330                                        \n\
                                                    \n\
layout (location = 0) in vec3 pos;                  \n\
                                                    \n\
uniform mat4 model;                                 \n\
                                                    \n\
void main(){                                        \n\
    gl_Position = model * vec4(pos.x, pos.y, pos.z, 1.0);   \n\
}";

// fragment shader
static const char* triangle_fShader = "                      \n\
#version 330                                        \n\
                                                    \n\
out vec4 color;                                     \n\
                                                    \n\
void main(){                                        \n\
    color = vec4(1.0, 1.0, 0.5, 1.0);               \n\
}";

int main(){
    // initialise GLFW
    if (!glfwInit()) {
        std::cout << "GLFW initialisation failed." << std::endl;

        glfwTerminate();

        return 1;
    }

    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // make window unresizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test OpenGL", NULL, NULL);

    if(!mainWindow){
        std::cout << "GLFW window creation failed." << std::endl;

        glfwTerminate();

        return 1;
    }

    // get buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // allow modern extension features
    glewExperimental = GL_TRUE;

    // initialise GLEW
    if(glewInit() != GLEW_OK){
        std::cout << "GLEW initialisation failed." << std::endl;

        glfwDestroyWindow(mainWindow);
        glfwTerminate();

        return 1;
    }

    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // create triangle
    opengl_utils::CreateTriangle(&triangle_VAO, &triangle_VBO);

    // compile trangle program with It's vertex and fragment shaders
    opengl_utils::CompileShaders(&triangle_program, triangle_fShader, triangle_vShader);

    // get uniform location of the "model" uniform and assign it to "triangle_uniformModel"
    triangle_uniformModel = glGetUniformLocation(triangle_program, "model");

    while (!glfwWindowShouldClose(mainWindow))
    {
        // get and handle user input events
        glfwPollEvents();

        // clear the window with black color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // opengl_utils::DrawMovingAnim(&triangle_direction, &triangle_offset, &triangle_maxOffset, &triangle_increment);
        opengl_utils::DrawScalingAnim(&triangle_scaleDir, &triangle_curSize, triangle_incrSize, triangle_maxSize, triangle_minSize);
        opengl_utils::DrawRotatingAnim(&triangle_curAngle, triangle_incrAngle);

        // use the compiled triangle program
        glUseProgram(triangle_program);

        // make a matrix identity
        glm::mat4 triangle_matrixIden = glm::mat4(1.0f);

        // triangle_matrixIden = glm::translate(triangle_matrixIden, glm::vec3(triangle_offset, 0.0f , 0.0f));
        triangle_matrixIden = glm::scale(triangle_matrixIden, glm::vec3(triangle_curSize, triangle_curSize, 1.0f));
        triangle_matrixIden = glm::rotate(triangle_matrixIden, glm::radians(triangle_curAngle), glm::vec3(0.0f, 0.0f, 1.0f));

        // set "model" uniform inside triangle program to triangle's matrix identity using the address saved in "triangle_uniformModel"
        glUniformMatrix4fv(triangle_uniformModel, 1, GL_FALSE, glm::value_ptr(triangle_matrixIden));

        glBindVertexArray(triangle_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers
        glfwSwapBuffers(mainWindow);
    }
    
}