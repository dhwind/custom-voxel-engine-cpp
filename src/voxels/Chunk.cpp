#include "Chunk.hpp"
#include <math.h>

Chunk::Chunk()
{
    voxels = new voxel[CHUNK_VOL];

    for (int y = 0; y < CHUNK_H; y++)
    {
        for (int z = 0; z < CHUNK_D; z++)
        {
            for (int x = 0; x < CHUNK_W; x++)
            {
                int id = y <= (sin(x * 0.3f) * 0.5f + 0.5f) * 10;
                // int id = 2;

                if (y <= 2)
                    id = 2;
                voxels[(y * CHUNK_D + z) * CHUNK_H + x].id = id;
            }
        }
    }
}

Chunk::~Chunk()
{
    delete[] voxels;
}