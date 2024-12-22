#include "NoiseGenerator.hpp"
#include "Mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTEX_SIZE (3 + 2)

#define IS_IN(X, Y, Z) ((X) >= 0 && (X) < CHUNK_W && (Y) >= 0 && (Y) < CHUNK_H && (Z) >= 0 && (Z) < CHUNK_D)
#define VOXEL(X, Y, Z) (chunk->voxels[((Y) * CHUNK_D + (Z)) * CHUNK_W + (X)])
#define IS_BLOCKED(X, Y, Z) ((IS_IN(X, Y, Z)) && VOXEL(X, Y, Z).id)

NoiseGenerator::NoiseGenerator(size_t capacity) : capacity(capacity)
{
    buffer.reserve(capacity * VERTEX_SIZE * 6);
}

Mesh *NoiseGenerator::render(Chunk *chunk)
{
    std::vector<GLuint> indices = {};

    for (int y = 0; y < CHUNK_H; y++)
    {
        for (int z = 0; z < CHUNK_D; z++)
        {
            for (int x = 0; x < CHUNK_W; x++)
            {
                voxel vox = chunk->voxels[((y) * 16 + (z)) * 16 + (x)];
                unsigned int id = vox.id;

                if (!id)
                {
                    continue;
                }

                float uvsize = 1.0f / 16.0f;
                float u = (id % 16) * uvsize;
                float v = 1 - ((1 + id / 16) * uvsize);

                // --- Верхняя грань ---
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(1.0f);

                // --- Нижняя грань ---
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(0.0f);

                // --- Правая грань ---
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(1.0f);
                buffer.push_back(0.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(1.0f);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(0.0f);
                buffer.push_back(0.0f);

                // --- Левая грань ---
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u);
                buffer.push_back(v);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v + uvsize);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u);
                buffer.push_back(v + uvsize);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u);
                buffer.push_back(v);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v + uvsize);

                // --- Передняя грань ---
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u);
                buffer.push_back(v);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v + uvsize);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u);
                buffer.push_back(v + uvsize);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u);
                buffer.push_back(v);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z + 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v + uvsize);

                // --- Задняя грань ---
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v + uvsize);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u);
                buffer.push_back(v + uvsize);
                buffer.push_back(x - 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u + uvsize);
                buffer.push_back(v);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y - 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u);
                buffer.push_back(v);
                buffer.push_back(x + 0.5f);
                buffer.push_back(y + 0.5f);
                buffer.push_back(z - 0.5f);
                buffer.push_back(u);
                buffer.push_back(v + uvsize);
            }
        }
    }

    std::vector<Vertex> vertexData = get_vertex_data(buffer);

    return new Mesh(vertexData, indices, "res/textures/blocks/ground.png");
}