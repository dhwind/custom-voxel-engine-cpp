#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

#define VERTEX_POSITIONS_COUNT 5

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, const std::string &spritePath) : vertices(vertices), indices(indices), texture(spritePath)
{
    glGenBuffers(1, &(this->VBO));
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->EBO));

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
    glEnableVertexAttribArray(0); // positions

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1); // texture coordinates

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &(this->VAO));
    glDeleteBuffers(1, &(this->VBO));
}

void Mesh::draw(GLuint primitive)
{
    this->texture.bind();
    glBindVertexArray(this->VAO);

    if (this->EBO != 0)
    {
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(primitive, this->indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(primitive, 0, this->vertices.size());
    }

    glBindVertexArray(0);
}

void Mesh::draw()
{
    this->draw(GL_TRIANGLES);
}

std::vector<Vertex> get_vertex_data(std::vector<GLfloat> vertexArr)
{
    std::vector<Vertex> vertexData;

    for (int i = 0; i < vertexArr.size(); i += VERTEX_POSITIONS_COUNT)
    {
        Vertex vertex;

        vertex.position = glm::vec3(vertexArr[i], vertexArr[i + 1], vertexArr[i + 2]);
        vertex.texCoords = glm::vec2(vertexArr[i + 3], vertexArr[i + 4]);

        vertexData.push_back(vertex);
    }

    return vertexData;
}
