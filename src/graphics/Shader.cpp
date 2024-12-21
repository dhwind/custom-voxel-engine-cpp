#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../window/Window.hpp"
#include "../utils/Logger.hpp"
#include "Shader.hpp"

Shader::Shader(GLuint id) : id(id)
{
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::use()
{
    glUseProgram(this->id);
}

// Function to get a shader type name
std::string get_shader_type_str(GLenum shaderType)
{
    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
        return "VERTEX";
    case GL_FRAGMENT_SHADER:
        return "FRAGMENT";
    case GL_GEOMETRY_SHADER:
        return "GEOMETRY";
    case GL_COMPUTE_SHADER:
        return "COMPUTE";
    case GL_TESS_CONTROL_SHADER:
        return "TESS_CONTROL";
    case GL_TESS_EVALUATION_SHADER:
        return "TESS_EVALUATION";
    default:
        return "UNKNOWN";
    }
}

// Function to read shader code from file
std::string read_shader_file(std::string filePath)
{
    std::string loggerPrefix = "SHADER::FILE";
    std::ifstream shaderFile;

    shaderFile.open(filePath);

    if (!shaderFile.is_open())
    {
        Logger::error("could not open a file \"" + filePath + "\"!", loggerPrefix);
        return "";
    }

    if (shaderFile.bad())
    {
        Logger::error("badbit error in the file \"" + filePath + "\"!", loggerPrefix);
        return "";
    }

    if (shaderFile.fail())
    {
        Logger::error("failbit error in the file \"" + filePath + "\"!", loggerPrefix);
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();

    shaderFile.close();

    return shaderStream.str();
}

// Compile shader function
GLuint compile_shader(GLenum shaderType, const std::string &shaderFile)
{
    std::string loggerPrefix = "SHADER::COMPILE";

    try
    {
        std::string typeStr = get_shader_type_str(shaderType);
        std::string shaderStream = read_shader_file(shaderFile);

        if (shaderStream.empty())
        {
            throw std::runtime_error("cannot load a " + typeStr + " shader file!");
        }

        GLuint shader;
        GLint success;
        GLchar infoLog[512];

        const GLchar *shaderSource = shaderStream.c_str();

        shader = glCreateShader(shaderType);

        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw std::runtime_error("compilation failed!\n\t" + static_cast<std::string>(infoLog));
        }

        Logger::debug(typeStr + " shader was successfully compiled!", loggerPrefix);
        return shader;
    }
    catch (const std::exception &e)
    {
        Logger::error(e.what(), loggerPrefix);
        return 0;
    }
}

std::unique_ptr<Shader> Shader::create(const std::string &vertexFile, const std::string &fragmentFile)
{
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Create, compile and get a compilation status of a shaders
    vertex = compile_shader(GL_VERTEX_SHADER, vertexFile);
    fragment = compile_shader(GL_FRAGMENT_SHADER, fragmentFile);

    if (vertex == 0 || fragment == 0)
    {
        Window::terminate();
    }

    // Shader program
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);

        Logger::error("compilation failed!\n\t" + static_cast<std::string>(infoLog), "SHADER::PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        glDeleteProgram(program);
        return nullptr;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return std::make_unique<Shader>(program);
}

void Shader::uniformMatrix(const std::string &name, glm::mat4 matrix)
{
    int location = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::uniform1f(const std::string &name, float x)
{
    int location = glGetUniformLocation(this->id, name.c_str());
    glUniform1f(location, x);
}