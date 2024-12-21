
#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <memory>

class Shader
{
public:
    Shader(GLuint id);
    ~Shader();

    GLuint id;

    static std::unique_ptr<Shader> create(const std::string &vertexFile, const std::string &fragmentFile);

    void use();
    void uniformMatrix(const std::string &name, glm::mat4 matrix);
    void uniform4f(const std::string &name, float x, float y, float z, float w);
    void uniform1f(const std::string &name, float x);
};

extern std::string read_shader_file(std::string filePath);

#endif /* GRAPHICS_SHADER_HPP */