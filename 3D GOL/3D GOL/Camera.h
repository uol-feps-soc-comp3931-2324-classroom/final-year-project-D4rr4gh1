#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float fov;

    bool moveForward, moveBackward, moveLeft, moveRight, speedUp, slowDown = false;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f), fov(45.0f) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(GLFWwindow *window, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset);

    void ProcessMouseScroll(float yoffset);



private: 
    void updateCameraVectors();

};

#endif // !CAMERA_H
