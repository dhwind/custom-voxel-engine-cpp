#ifndef GRAPHICS_TEXTURE_HPP
#define GRAPHICS_TEXTURE_HPP

#include <memory>

class Texture
{
public:
    GLuint id;
    int width;
    int height;
    int nrChannels;
    std::string spritePath;

    Texture(const std::string &spritePath);
    ~Texture();

    void bind();
};

#endif /* GRAPHICS_TEXTURE_HPP */