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

// VAO and VBO of triangle
GLuint triangle_VAO, triangle_VBO;

// IBO (index buffer object) of triangle
GLuint triangle_IBO;

// triangle program
GLuint triangle_program;

// triangle uniform model address
GLuint triangle_uniformModel;

// pyramid uniform projection address
GLuint triangle_uniformProjection;

// triangle moving animation values
bool triangle_direction = true;
float triangle_offset = 0.0f;
float triangle_maxOffset = 0.7f;
float triangle_increment = 0.01f;

// triangle scaling animation values
bool triangle_scaleDir = true;
float triangle_curSize = 0.01f;
float triangle_incrSize = 0.0008f;
float triangle_maxSize = 0.03f;
float triangle_minSize = 0.0f;

// triangle rotating animation values
float triangle_curAngle = 0.0f;
float triangle_incrAngle = 1.0f;

// vertex shader
static const char* triangle_vShader = "                      \n\
#version 330                                        \n\
                                                    \n\
layout (location = 0) in vec3 pos;                  \n\
                                                    \n\
out vec4 vCol;                                      \n\
                                                    \n\
uniform mat4 model;                                 \n\
uniform mat4 projection;                                 \n\
                                                    \n\
void main(){                                        \n\
    gl_Position = projection * model * vec4(pos, 1.0);           \n\
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);       \n\
}";

// fragment shader
static const char* triangle_fShader = "                      \n\
#version 330                                        \n\
                                                    \n\
in vec4 vCol;                                       \n\
                                                    \n\
out vec4 color;                                     \n\
                                                    \n\
void main(){                                        \n\
    color = vCol;                                   \n\
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

    // enable depth buffer/z-buffer
    glEnable(GL_DEPTH_TEST);

    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // create triangle
    opengl_utils::CreatePyramid(&triangle_VAO, &triangle_VBO, &triangle_IBO);

    // compile trangle program with It's vertex and fragment shaders
    opengl_utils::CompileShaders(&triangle_program, triangle_fShader, triangle_vShader);

    glm::mat4 triangle_projection = glm::perspective(45.0f, (float)bufferWidth / (float)bufferHeight, 0.1f, 100.0f);

    // get uniform location of the "model" uniform and assign it to "triangle_uniformModel"
    triangle_uniformModel = glGetUniformLocation(triangle_program, "model");

    // get uniform location of the "projection" uniform and assign it to "triangle_uniformProjection"
    triangle_uniformProjection = glGetUniformLocation(triangle_program, "projection");

    while (!glfwWindowShouldClose(mainWindow))
    {
        // get and handle user input events
        glfwPollEvents();

        // clear the window with black color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // rotating anim
        opengl_utils::DrawRotatingAnim(&triangle_curAngle, triangle_incrAngle);
        opengl_utils::DrawMovingAnim(&triangle_direction, &triangle_offset, &triangle_maxOffset, &triangle_increment);

        // use the compiled triangle program
        glUseProgram(triangle_program);

        // make a matrix identity
        glm::mat4 triangle_matrixIden = glm::mat4(1.0f);

        triangle_matrixIden = glm::scale(triangle_matrixIden, glm::vec3(1.0f, 1.0f, 1.0f));
        triangle_matrixIden = glm::translate(triangle_matrixIden, glm::vec3(0.0f, 0.2f, -3.0f));
        triangle_matrixIden = glm::rotate(triangle_matrixIden, glm::radians(triangle_curAngle), glm::vec3(0.0f, 1.0f, 0.0f));

        // set "model" uniform inside triangle program to triangle's matrix identity using the address saved in "triangle_uniformModel"
        glUniformMatrix4fv(triangle_uniformModel, 1, GL_FALSE, glm::value_ptr(triangle_matrixIden));

        glUniformMatrix4fv(triangle_uniformProjection, 1, GL_FALSE, glm::value_ptr(triangle_projection));

        glBindVertexArray(triangle_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_IBO);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // swap buffers
        glfwSwapBuffers(mainWindow);
    }
}