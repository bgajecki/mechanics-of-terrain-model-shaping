#pragma once

#include <Chunk.hpp>
#include <random>

class World final : public engine::Chunk
{
public:

	enum VoxelType
	{
		TERRAIN = 0u,
		WATER
	};

	/**
	* Terrain constructor.
	*/
	World();
	~World() = default;
	virtual void update(float) override;
	bool isRaining;
private:
	void setWaterVoxel(engine::Voxel&);
	void setTerrainVoxel(engine::Voxel&);

	void physics();
	void rain();

	engine::Color waterColor, terrainColor;
};