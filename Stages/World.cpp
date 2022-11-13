#include "World.hpp"
#include "World.hpp"
#include "World.hpp"
#include "World.hpp"
#include "World.hpp"
#include "World.hpp"

World::World()
	: engine::Chunk(), isRaining(true), terrainColor(0.0f, 1.0f, 0.0f, 1.0f), waterColor(0.0f, 0.0f, 1.0f, 0.8f)
{
    this->resize(64u);
    for (size_t x = 0; x < this->chunkSize; x++)
    {
        for (size_t y = 0; y < this->chunkSize / 2u; y++)
        {
            for (size_t z = 0; z < this->chunkSize; z++)
            {
                int dx = x - 32;
                int dz = z - 32;
                dx = dx > 0 ? dx : -dx;
                dz = dz > 0 ? dz : -dz;
                if (y > dx && y > dz && y > 16)
                    continue;
                this->setTerrainVoxel(this->voxels[x][y][z]);
            }
        }
    }
}

void World::update(float dt)
{
    this->physics();
    this->rain();
    this->refresh();
}

void World::setWaterVoxel(engine::Voxel& voxel)
{
    voxel.active = true;
    voxel.color = waterColor;
    voxel.type = WATER;
    voxel.isForced = false;
}

void World::setTerrainVoxel(engine::Voxel& voxel)
{
    voxel.active = true;
    voxel.color = terrainColor;
    voxel.type = TERRAIN;
    voxel.isForced = false;
}

void World::physics()
{
    for (size_t x = 0; x < this->chunkSize; x++)
    {
        for (size_t y = 0; y < this->chunkSize; y++)
        {
            for (size_t z = 0; z < this->chunkSize; z++)
            {
                engine::Voxel& voxel = this->voxels[x][y][z];

                if (voxel.active == false)
                {
                    continue;
                }

                if (voxel.type != WATER)
                {
                    continue;
                }

                if (y - 1 < 0)
                {
                    continue;
                }
                
                // Down
                if (this->voxels[x][y - 1][z].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x][y - 1][z]);
                    continue;
                }

                // Left
                if (this->voxels[x - 1][y - 1][z].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x - 1][y - 1][z]);
                    continue;
                }

                // Right
                if (this->voxels[x + 1][y - 1][z].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x + 1][y - 1][z]);
                    continue;
                }

                // Left
                if (this->voxels[x][y - 1][z - 1].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x][y - 1][z - 1]);
                    continue;
                }

                // Right
                if (this->voxels[x][y - 1][z + 1].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x][y - 1][z + 1]);
                    continue;
                }



                //
                if (this->voxels[x - 1][y - 1][z - 1].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x - 1][y - 1][z - 1]);
                    continue;
                }

                //
                if (this->voxels[x - 1][y - 1][z + 1].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x - 1][y - 1][z + 1]);
                    continue;
                }

                //
                if (this->voxels[x + 1][y - 1][z - 1].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x + 1][y - 1][z - 1]);
                    continue;
                }

                //
                if (this->voxels[x + 1][y - 1][z + 1].active == false)
                {
                    voxel.active = false;
                    this->setWaterVoxel(this->voxels[x + 1][y - 1][z + 1]);
                    continue;
                }

                //FORCED
                if (voxel.isForced == true)
                {
                    // Left
                    if (this->voxels[x - 1][y][z].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x - 1][y][z]);
                        continue;
                    }

                    // Right
                    if (this->voxels[x + 1][y][z].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x + 1][y][z]);
                        continue;
                    }

                    // Left
                    if (this->voxels[x][y][z - 1].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x][y][z - 1]);
                        continue;
                    }

                    // Right
                    if (this->voxels[x][y][z + 1].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x][y][z + 1]);
                        continue;
                    }



                    //
                    if (this->voxels[x - 1][y][z - 1].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x - 1][y][z - 1]);
                        continue;
                    }

                    //
                    if (this->voxels[x - 1][y][z + 1].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x - 1][y][z + 1]);
                        continue;
                    }

                    //
                    if (this->voxels[x + 1][y][z - 1].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x + 1][y][z - 1]);
                        continue;
                    }

                    //
                    if (this->voxels[x + 1][y][z + 1].active == false)
                    {
                        voxel.active = false;
                        this->setWaterVoxel(this->voxels[x + 1][y][z + 1]);
                        continue;
                    }

                    ////////////////////////////////////////////////////////////// FORCING

                    // Left
                    if (this->voxels[x - 1][y][z].type == WATER)
                    {
                        this->voxels[x - 1][y][z].isForced = true;
                    }

                    // Right
                    if (this->voxels[x + 1][y][z].type == WATER)
                    {
                        this->voxels[x + 1][y][z].isForced = true;
                    }

                    // Left
                    if (this->voxels[x][y][z - 1].type == WATER)
                    {
                        this->voxels[x][y][z - 1].isForced = true;
                    }

                    // Right
                    if (this->voxels[x][y][z + 1].type == WATER)
                    {
                        this->voxels[x][y][z + 1].isForced = true;
                    }



                    //
                    if (this->voxels[x - 1][y][z - 1].type == WATER)
                    {
                        this->voxels[x - 1][y][z - 1].isForced = true;
                    }

                    //
                    if (this->voxels[x - 1][y][z + 1].type == WATER)
                    {
                        this->voxels[x - 1][y][z + 1].isForced = true;
                    }

                    //
                    if (this->voxels[x + 1][y][z - 1].type == WATER)
                    {
                        this->voxels[x + 1][y][z - 1].isForced = true;
                    }

                    //
                    if (this->voxels[x + 1][y][z + 1].type == WATER)
                    {
                        this->voxels[x + 1][y][z + 1].isForced = true;
                    }

                }

                ////////////////////////////////////////////////////////////// FORCING

                // Left
                if (this->voxels[x - 1][y - 1][z].type == WATER)
                {
                    this->voxels[x - 1][y - 1][z].isForced = true;
                }

                // Right
                if (this->voxels[x + 1][y - 1][z].type == WATER)
                {
                    this->voxels[x + 1][y - 1][z].isForced = true;
                }

                // Left
                if (this->voxels[x][y - 1][z - 1].type == WATER)
                {
                    this->voxels[x][y - 1][z - 1].isForced = true;
                }

                // Right
                if (this->voxels[x][y - 1][z + 1].type == WATER)
                {
                    this->voxels[x][y - 1][z + 1].isForced = true;
                }



                //
                if (this->voxels[x - 1][y - 1][z - 1].type == WATER)
                {
                    this->voxels[x - 1][y - 1][z - 1].isForced = true;
                }

                //
                if (this->voxels[x - 1][y - 1][z + 1].type == WATER)
                {
                    this->voxels[x - 1][y - 1][z + 1].isForced = true;
                }

                //
                if (this->voxels[x + 1][y - 1][z - 1].type == WATER)
                {
                    this->voxels[x + 1][y - 1][z - 1].isForced = true;
                }

                //
                if (this->voxels[x + 1][y - 1][z + 1].type == WATER)
                {
                    this->voxels[x + 1][y - 1][z + 1].isForced = true;
                }

                /*
                bool isFinded = false;
                for (int near_x = -6; near_x < 7; near_x++)
                {
                    for (int near_z = -6; near_z < 7; near_z++)
                    {
                        if (x - near_x < 0)
                        {
                            continue;
                        }

                        if (z - near_z < 0)
                        {
                            continue;
                        }

                        if (x + near_x >= 63)
                        {
                            continue;
                        }

                        if (z + near_z >= 63)
                        {
                            continue;
                        }

                        if (this->voxels[x + near_x][y - 1][z + near_z].active == false)
                        {
                            int direction_x = near_x == 0 ? 0 : near_x > 0 ? 1 : -1;
                            int direction_z = near_z == 0 ? 0 : near_z > 0 ? 1 : -1;
                            if (this->voxels[x + direction_x][y][z + direction_z].active == false)
                            {
                                voxel.active = false;
                                this->setWaterVoxel(this->voxels[x + direction_x][y][z + direction_z]);
                                isFinded = true;
                                break;
                            }

                        }
                    }
                    if (isFinded == true)
                    {
                        break;
                    }
                }

                isFinded = false;
                */
            }
        }
    }
}

void World::rain()
{
    if (this->isRaining)
    {
        const size_t waterUnits = 5u;
        std::random_device device;
        std::mt19937 generator(device());
        std::uniform_int_distribution<size_t> distribution(1u, 62u);

        size_t yStart = 63, yEnd = 64;
        for (size_t i = 0u; i < waterUnits; i++)
        {
            size_t x = distribution(generator);
            size_t z = distribution(generator);

            for (size_t y = yStart; y < yEnd; y++)
            {
                //for (int dx = -1; dx < 1; dx++)
                //{
                //    for (int dz = -1; dz < 1; dz++)
                //    {
                this->setWaterVoxel(this->voxels[x][y][z]);
                //    }
                //}
            }

        }
    }
}
