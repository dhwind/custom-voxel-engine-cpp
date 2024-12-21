#ifndef WINDOW_WINDOW_HPP
#define WINDOW_WINDOW_HPP

#include <glm/glm.hpp>

class GLFWwindow;

class Window
{
public:
    static GLFWwindow *window;
    static int initialize(int width, int height, const char *title);
    static bool shouldClose();
    static void swapBuffers();
    static void setShouldClose(bool flag);
    static void terminate();

    static void setBgColor(glm::vec3 color);
    static void clear();
};

#endif // WINDOW_WINDOW_HPP