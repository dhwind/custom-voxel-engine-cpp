#include <cstdint>

#ifndef VOXELS_CHUNK_HPP
#define VOXELS_CHUNK_HPP

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

struct voxel
{
    uint8_t id;
};

class Chunk
{
public:
    voxel *voxels;
    Chunk();
    ~Chunk();
};
#endif // VOXELS_CHUNK_HPP