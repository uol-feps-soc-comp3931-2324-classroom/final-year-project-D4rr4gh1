#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"


glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

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

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch -= yoffset; // Reversed since y-coordinates range from bottom to top

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
