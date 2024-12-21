#ifndef GRAPHICS_NOISE_GENERATOR_HPP
#define GRAPHICS_NOISE_GENERATOR_HPP

#include "../voxels/Chunk.hpp"
#include "Mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// terrain generation using Perlin Noise Algorithm
class NoiseGenerator
{
private:
    std::vector<GLfloat> buffer;
    size_t capacity;

public:
    NoiseGenerator(size_t capacity);

    Mesh *render(Chunk *chunk);
};
#endif // GRAPHICS_NOISE_GENERATOR_HPP