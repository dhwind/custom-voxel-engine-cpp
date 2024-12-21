#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../utils/Logger.hpp"
#include "Window.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *Window::window;

int Window::initialize(int width, int height, const char *title)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        Logger::error("can't create a GLFW window", "WINDOW::INIT");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        Logger::error("can't load GLAD", "WINDOW::INIT");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 0;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

void Window::setShouldClose(bool flag)
{
    glfwSetWindowShouldClose(window, flag);
}

void Window::terminate()
{
    glfwTerminate();
    exit(-1);
}

void Window::setBgColor(glm::vec3 color)
{
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}