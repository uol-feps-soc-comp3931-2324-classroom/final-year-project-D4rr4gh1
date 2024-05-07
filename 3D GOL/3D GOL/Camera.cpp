#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

// Define the view of the camera
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

// Process the keyboard input for the camera
void Camera::ProcessKeyboard(GLFWwindow *window, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (moveForward)
        Position += Front * velocity;
    if (moveBackward)
        Position -= Front * velocity;
    if (moveLeft)
        Position -= Right * velocity;
    if (moveRight)
        Position += Right * velocity;
    if (speedUp)
        MovementSpeed += deltaTime * 5.f;
    else if (slowDown)
        MovementSpeed < 5.f ? MovementSpeed = 5.f : MovementSpeed -= deltaTime * 5.f;
}

// Process the mouse movement for the camera
void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch -= yoffset;

    // Ensure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateCameraVectors();
}

// Process the mouse scroll for the camera
void Camera::ProcessMouseScroll(float yoffset) {

    fov -= (float)yoffset;

    // Ensure that the field of view is within the bounds of 1.0f and 90.0f
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 90.0f) fov = 90.0f;
}


// Update the camera vectors
void Camera::updateCameraVectors() {
    glm::vec3 front;

    // Calculate the new Front vector
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    
    // Update the Front, Right, and Up vectors
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
