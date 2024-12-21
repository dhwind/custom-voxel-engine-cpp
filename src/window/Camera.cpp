#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Events.hpp"
#include "Camera.hpp"

// inital camera pos
glm::vec3 Camera::pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Camera::front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

float Camera::yaw = -90.0f;
float Camera::pitch = 0.0f;

float Camera::sensitivity = 0.2f;
float Camera::speed = 0.2f;

void Camera::process()
{
    if (Events::jpressed(GLFW_KEY_ESCAPE))
    {
        Window::setShouldClose(true);
    }

    float cameraSpeed = Camera::speed;

    if (Events::pressed(GLFW_KEY_LEFT_SHIFT))
    {
        cameraSpeed *= 3;
    }
    else if (Events::jpressed(GLFW_KEY_LEFT_SHIFT))
    {
        cameraSpeed /= 3;
    }

    if (Events::pressed(GLFW_KEY_SPACE))
        pos += cameraSpeed * up;
    if (Events::pressed(GLFW_KEY_LEFT_ALT))
        pos -= cameraSpeed * up;
    if (Events::pressed(GLFW_KEY_W))
        pos += cameraSpeed * front;
    if (Events::pressed(GLFW_KEY_S))
        pos -= cameraSpeed * front;
    if (Events::pressed(GLFW_KEY_A))
        pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if (Events::pressed(GLFW_KEY_D))
        pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;

    yaw += Events::deltaX * Camera::sensitivity;
    pitch += Events::deltaY * Camera::sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
}

void Camera::changeSensitivity(float newSensitivity)
{
    Camera::sensitivity = newSensitivity;
}

void Camera::changeSpeed(float newSpeed)
{
    Camera::speed = newSpeed;
}