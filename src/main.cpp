#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Mesh.hpp"

#include "window/Window.hpp"
#include "window/Events.hpp"

#include "graphics/Shader.hpp"
#include "window/Camera.hpp"
#include "utils/Logger.hpp"

#include "voxels/Chunk.hpp"
#include "graphics/NoiseGenerator.hpp"

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 800;

// clang-format off
std::vector<GLfloat> vertices = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // 0
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,    // 1
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    // 2
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   // 3
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 4
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    // 5
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,    // 6
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // 7
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 8
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 9
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 10
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    // 11
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    // 12
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    // 13
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,    // 14
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f    // 15
};


std::vector<GLuint> indices = {
    // Передняя грань
    0, 1, 2,
    2, 3, 0,

    // Задняя грань
    4, 5, 6,
    6, 7, 4,

    // Левая грань
    8, 9, 10,
    10, 4, 8,

    // Правая грань
    11, 2, 12,
    12, 13, 11,

    // Верхняя грань
    10, 14, 5,
    5, 4, 10,

    // Нижняя грань
    3, 2, 11,
    11, 15, 3
};
// clang-format on

int main(void)
{
    Window::initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "InvasionDefender\0");
    Events::initialize();

    std::unique_ptr<Shader> shader = Shader::create("res/shaders/main.vs", "res/shaders/main.fs");

    NoiseGenerator renderer(1024 * 1024);
    Chunk *chunk = new Chunk();
    Mesh *mesh = renderer.render(chunk);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, 0, 0));

    while (!Window::shouldClose())
    {

        glm::vec3 bgColor = {0.2f, 0.3f, 0.3f};

        Window::setBgColor(bgColor);
        Window::clear();

        glm::mat4 view = glm::lookAt(Camera::pos, Camera::pos + Camera::front, Camera::up);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        Camera::process();

        shader->uniformMatrix("view", view);
        shader->uniformMatrix("projection", projection);
        shader->uniformMatrix("model", model);
        shader->use();

        mesh->draw();

        Window::swapBuffers();
        Events::pullEvents();
    }

    shader->~Shader();

    Window::terminate();
    return 0;
}
