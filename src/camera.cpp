#include <camera.h>

camera::camera(){
    
}

camera::camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startPitch, GLfloat startYaw, GLfloat startMovementSpeed, GLfloat startTurnSpeed, GLfloat startBoostSpeed){
    position = startPosition;
    worldUp = startUp;
    pitch = startPitch;
    yaw = startYaw;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    movementSpeed = startMovementSpeed;
    turnSpeed = startTurnSpeed;
    boostSpeed = startBoostSpeed;

    update();
}

void camera::keyControl(bool* keys, GLfloat deltaTime){
    GLfloat velocity = movementSpeed * deltaTime;

    if(keys[GLFW_KEY_LEFT_SHIFT]){
        velocity *= boostSpeed;
    }

    if(keys[GLFW_KEY_W]){
        position += front * velocity;
    }

    if(keys[GLFW_KEY_S]){
        position -= front * velocity;
    }

    if(keys[GLFW_KEY_A]){
        position -= right * velocity;
    }

    if(keys[GLFW_KEY_D]){
        position += right * velocity;
    }

    if(keys[GLFW_KEY_SPACE]){
        position += worldUp * velocity;
    }

    if(keys[GLFW_KEY_LEFT_CONTROL]){
        position -= worldUp * velocity;
    }
}

void camera::mouseControl(GLfloat xChange, GLfloat yChange){
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if (pitch > 89.0f){
        pitch = 89.0f;
    }

    if (pitch < -89.0f){
        pitch = -89.0f;
    }

    update();
}

glm::mat4 camera::calculateViewMatrix(){
    return glm::lookAt(position, position + front, up);
}

void camera::update(){
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));

    up = glm::normalize(glm::cross(right, front));
}