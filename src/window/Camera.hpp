#ifndef WINDOW_CAMERA_HPP
#define WINDOW_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    static glm::vec3 pos;
    static glm::vec3 front;
    static glm::vec3 up;

    static float yaw;
    static float pitch;

    static float sensitivity;
    static float speed;

    static void process();
    static void changeSensitivity(float newSensitivity);
    static void changeSpeed(float newSpeed);
};
#endif // WINDOW_CAMERA_HPP