#include <iostream>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Events.hpp"

#include "../utils/Logger.hpp"

#define _MOUSE_BUTTONS 1024

const int BUFFER_SIZE = _MOUSE_BUTTONS + 8;

bool *Events::_keys;
unsigned int *Events::_frames;
unsigned int Events::_current;

float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;

bool Events::_cursor_locked = true;
bool Events::_cursor_started = false;

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (Events::_cursor_locked)
    {
        Events::x = xpos;
        Events::y = ypos;
        Events::_cursor_locked = false;
    }
    else
    {
        Events::_cursor_started = true;
    }

    Events::deltaX += xpos - Events::x;
    Events::deltaY += Events::y - ypos;

    Events::x = xpos;
    Events::y = ypos;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        Events::_keys[_MOUSE_BUTTONS + button] = true;
        Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::_keys[_MOUSE_BUTTONS + button] = false;
        Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        Events::_keys[key] = true;
        Events::_frames[key] = Events::_current;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::_keys[key] = false;
        Events::_frames[key] = Events::_current;
    }
}

int Events::initialize()
{
    GLFWwindow *window = Window::window;
    _keys = new bool[BUFFER_SIZE];
    _frames = new unsigned int[BUFFER_SIZE];

    std::memset(_keys, false, BUFFER_SIZE * sizeof(bool));
    std::memset(_frames, 0, BUFFER_SIZE * sizeof(unsigned int));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    return 0;
}

void Events::pullEvents()
{
    _current++;
    deltaX = 0.0f;
    deltaY = 0.0f;

    /* Poll for and process events */
    glfwPollEvents();
}

bool Events::pressed(int keycode)
{
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
    {
        return false;
    }

    return _keys[keycode];
}

bool Events::jpressed(int keycode)
{
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
    {
        return false;
    }

    return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::clicked(int button)
{
    int index = _MOUSE_BUTTONS + button;

    if (index >= BUFFER_SIZE)
    {
        return false;
    }

    return _keys[index];
}

bool Events::jclicked(int button)
{
    int index = _MOUSE_BUTTONS + button;

    if (index >= BUFFER_SIZE)
    {
        return false;
    }

    return _keys[index] && _frames[index] == _current;
}
