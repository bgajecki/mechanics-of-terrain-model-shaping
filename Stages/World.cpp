#include "World.hpp"

World::World()
	: engine::Chunk<engine::Color, NUMBER_OF_VOXEL_TYPES>() , isRaining(false), terrainColor(0.0f, 1.0f, 0.0f, 1.0f), waterColor(0.0f, 0.0f, 1.0f, 1.0f), terrainCorrosionScale(0.1f), waterEvaporationScale(0.1f)
{
    this->resize(64);
    this->setVoxelSize(0.005f);
    this->setVoxelTypeAttribute(TERRAIN, terrainColor);
    this->setVoxelTypeAttribute(WATER, waterColor);
    this->executeOnSelectedVoxels(0u, this->chunkSize, 0u, this->chunkSize / 2u, 0, this->chunkSize, [this](size_t x, size_t y, size_t z) {
        int dx = x - this->chunkSize / 2u;
        int dz = z - this->chunkSize / 2u;
        dx = dx > 0 ? dx : -dx;
        dz = dz > 0 ? dz : -dz;
        if (y > dx && y > dz && y > this->chunkSize / 4u)
            return;
        this->createTerrainVoxel(this->voxels[x][y][z]);
    });
}

void World::update(float dt)
{
    this->physics();
    this->rain();
    this->refresh();
}

void World::createWaterVoxel(engine::Voxel& voxel)
{
    voxel.setActive(true);
    voxel.setLifespan(100.0f);
    voxel.setType(WATER);
}

void World::createTerrainVoxel(engine::Voxel& voxel)
{
    voxel.setActive(true);
    voxel.setLifespan(200.0f);
    voxel.setType(TERRAIN);
}

void World::physics()
{
    this->executeOnEachVoxels([this](size_t x, size_t y, size_t z) {
        const engine::Voxel& voxel = this->voxels[x][y][z];

        if (voxel.isActive() == false)
        {
            return;
        }

        switch (voxel.getType())
        {
        case TERRAIN:
            this->terrainPhysics(x, y, z);
            break;
        case WATER:
            this->waterPhysics(x, y, z);
            break;
        }
    });
}

void World::rain()
{
    if (this->isRaining)
    {
        constexpr size_t waterUnits = 3u;
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
                this->createWaterVoxel(this->voxels[x][y][z]);
                //    }
                //}
            }

        }
    }
}

void World::terrainPhysics(size_t x, size_t y, size_t z)
{
    if (this->terrainFall(x, y, z))
        return;
    this->terrainCorrosion(x, y, z);
}

bool World::terrainFall(size_t x, size_t y, size_t z)
{
    engine::Voxel& voxel = this->voxels[x][y][z];
    if (y > 0)
    {
        if (this->voxels[x][y - 1][z].isActive() == false)
        {
            voxel.setActive(false);
            this->createTerrainVoxel(this->voxels[x][y - 1][z]);
            return true;
        }
    }
    return false;
}

void World::terrainCorrosion(size_t x, size_t y, size_t z)
{
    auto condition = [](const auto& voxel) -> auto {
        return voxel.getType() == WATER && voxel.isActive() == true;
    };

    auto function = [this](auto x1, auto y1, auto z1, auto x2, auto y2, auto z2) -> auto {
        this->voxels[x1][y1][z1].decreaseLifespan(this->terrainCorrosionScale);
        return true;
    };
        
    // Up
    if (y + 1 < this->chunkSize)
    {
        if (condition(this->voxels[x][y + 1][z]))
        {
            function(x, y, z, x, y + 1, z);
            return;
        }
    }

    this->vonNeumannNeighborhoodInteraction(x, y, z, x, y, z, condition, function);
}

void World::searchForHole(size_t x, size_t y, size_t z)
{
    engine::Voxel& voxel = this->voxels[x][y][z];
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

            if (x + near_x >= this->chunkSize - 1)
            {
                continue;
            }

            if (z + near_z >= this->chunkSize - 1)
            {
                continue;
            }

            if (this->voxels[x + near_x][y - 1][z + near_z].isActive() == false)
            {
                int direction_x = near_x == 0 ? 0 : near_x > 0 ? 1 : -1;
                int direction_z = near_z == 0 ? 0 : near_z > 0 ? 1 : -1;
                if (this->voxels[x + direction_x][y][z + direction_z].isActive() == false)
                {
                    voxel.setActive(false);
                    this->createWaterVoxel(this->voxels[x + direction_x][y][z + direction_z]);
                    return;
                }

            }
        }
    }
}

void World::waterPhysics(size_t x, size_t y, size_t z)
{
    if (this->waterFall(x, y, z))
        return;
    if (this->waterPush(x, y, z))
        return;
    this->waterEvaporation(x, y, z);
}

bool World::vonNeumannNeighborhoodInteraction(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2, VoxelInteractionCondition condition, VoxelInteractionFunction function)
{
    if (x2 > 0u)
    {
        if (condition(this->voxels[x2 - 1][y2][z2]))
        {
            function(x1, y1, z1, x2 - 1, y2, z2);
            return true;
        }
    }

    if (x2 + 1 < this->chunkSize)
    {
        if (condition(this->voxels[x2 + 1][y2][z2]))
        {
            function(x1, y1, z1, x2 + 1, y2, z2);
            return true;
        }
    }

    if (z2 > 0u)
    {
        if (condition(this->voxels[x2][y2][z2 - 1]))
        {
            function(x1, y1, z1, x2, y2, z2 - 1);
            return true;
        }
    }
    
    if (z2 + 1 < this->chunkSize)
    {
        if (condition(this->voxels[x2][y2][z2 + 1]))
        {
            function(x1, y1, z1, x2, y2, z2 + 1);
            return true;
        }
    }

    return false;
}

bool World::mooreNeighborhoodInteraction(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2, VoxelInteractionCondition condition, VoxelInteractionFunction function)
{
    if (this->vonNeumannNeighborhoodInteraction(x1, y1, z1, x2, y2, z2, condition, function))
        return true;

    if (x2 > 0u && z2 > 0u)
    {
        if (condition(this->voxels[x2 - 1][y2][z2 - 1]))
        {
            function(x1, y1, z1, x2 - 1, y2, z2 - 1);
            return true;
        }
    }

    if (x2 + 1 < this->chunkSize && z2 > 0u)
    {
        if (condition(this->voxels[x2 + 1][y2][z2 - 1]))
        {
            function(x1, y1, z1, x2 + 1, y2, z2 - 1);
            return true;
        }
    }

    if (x2 > 0u && z2 + 1 < this->chunkSize)
    {
        if (condition(this->voxels[x2 - 1][y2][z2 + 1]))
        {
            function(x1, y1, z1, x2 - 1, y2, z2 + 1);
            return true;
        }
    }

    if (x2 + 1 < this->chunkSize && z2 + 1 < this->chunkSize)
    {
        if (condition(this->voxels[x2 + 1][y2][z2 + 1]))
        {
            function(x1, y1, z1, x2 + 1, y2, z2 + 1);
            return true;
        }
    }

    return false;
}

bool World::waterFall(size_t x, size_t y, size_t z)
{
    engine::Voxel& voxel = this->voxels[x][y][z];
    auto condition = [](const auto& voxel) -> auto {
        return voxel.isActive() == false;
    };

    auto function = [this](auto x1, auto y1, auto z1, auto x2, auto y2, auto z2) -> auto {
        this->voxels[x1][y1][z1].setActive(false);
        this->createWaterVoxel(this->voxels[x2][y2][z2]);
        return true;
    };
    
    // Down
    if (y > 0)
    {
        if (condition(this->voxels[x][y - 1][z]))
            return function(x, y, z, x, y - 1, z);

        return this->mooreNeighborhoodInteraction(x, y, z, x, y - 1, z, condition, function);
    }
}

bool World::waterPush(size_t x, size_t y, size_t z)
{
    engine::Voxel& voxel = this->voxels[x][y][z];
    auto condition = [](const auto& voxel) -> auto {
        return voxel.getType() == WATER;
    };

    auto function = [this](auto x1, auto y1, auto z1, auto x2, auto y2, auto z2) -> auto {
        int xDiff = x2 - x1;
        int zDiff = z2 - z1;
        int i = 1;
        while (1)
        {

            if (x2 + xDiff * i < 1 || z2 + zDiff * i < 1
                || x2 + xDiff * i > this->chunkSize - 1 || z2 + zDiff * i > this->chunkSize - 1)
            {
                return false;
            }

            if (this->voxels[x2 + xDiff * i][y2][z2 + zDiff * i].isActive() == false)
            {
                break;
            }

            if (this->voxels[x2 + xDiff * i][y2][z2 + zDiff * i].getType() != WATER)
            {
                return false;
            }

            i++;
        }
        this->voxels[x1][y1][z1].setActive(false);
        this->createWaterVoxel(this->voxels[x2 + xDiff * i][y2][z2 + zDiff * i]);
        return true;
    };

    return this->mooreNeighborhoodInteraction(x, y, z, x, y - 1, z, condition, function);
}

void World::waterEvaporation(size_t x, size_t y, size_t z)
{
    engine::Voxel& voxel = this->voxels[x][y][z];
    if (y + 1 < this->chunkSize)
    {
        if (this->voxels[x][y + 1][z].isActive() == false
            && this->voxels[x][y + 1][z].getType() != WATER)
        {
            voxel.decreaseLifespan(this->waterEvaporationScale);
        }
    }
}
