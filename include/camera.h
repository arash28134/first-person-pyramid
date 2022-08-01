#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
public:
    camera();
    camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startPitch, GLfloat startYaw, GLfloat startMovementSpeed, GLfloat startTurnSpeed, GLfloat startBoostSpeed);

    // controlling keys, using inputs that window class gets
    void keyControl(bool* keys, GLfloat deltaTime);

    // controlling mouse movements
    void mouseControl(GLfloat xChange, GLfloat yChange);

    // calculating view matrix
    glm::mat4 calculateViewMatrix();
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat pitch;
    GLfloat yaw;

    GLfloat movementSpeed;
    GLfloat turnSpeed;

    // speed that gets multiplied with velocity when user presses left shift key
    GLfloat boostSpeed;

    // update function used for calculating front, up and right
    void update();
};