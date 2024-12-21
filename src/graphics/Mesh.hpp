
#ifndef GRAPHICS_MESH_HPP
#define GRAPHICS_MESH_HPP

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, const std::string &spritePath);
    ~Mesh();

    void draw(GLuint primitive);
    void draw();

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Texture texture;
};

extern std::vector<Vertex> get_vertex_data(const std::vector<GLfloat> &vertexArr);

#endif /* GRAPHICS_MESH_HPP */