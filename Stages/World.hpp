#pragma once

#include <Chunk.hpp>
#include <functional>
#include <random>

/**
* Terrain constructor.
*/
enum VoxelType
{
	TERRAIN = 0,
	WATER,
	NUMBER_OF_VOXEL_TYPES
};

class World final : public engine::Chunk<engine::Color, NUMBER_OF_VOXEL_TYPES>
{
	/**
	* Terrain constructor.
	*/
	using VoxelInteractionCondition = std::function<bool(const engine::Voxel&)>;
	/**
	* Terrain constructor.
	*/
	using VoxelInteractionFunction = std::function<bool(size_t, size_t, size_t, size_t, size_t, size_t)>;
public:

	/**
	* Terrain constructor.
	*/
	World();
	/**
	* Terrain constructor.
	*/
	~World() = default;

	/**
	* Terrain constructor.
	*/
	virtual void update(float) override;

	/**
	* Terrain constructor.
	*/
	bool isRaining;
private:
	/**
	* Terrain constructor.
	*/
	void createWaterVoxel(engine::Voxel&);

	/**
	* Terrain constructor.
	*/
	void createTerrainVoxel(engine::Voxel&);

	/**
	* Terrain constructor.
	*/
	void physics();

	/**
	* Terrain constructor.
	*/
	void rain();

	/**
	* Terrain constructor.
	*/
	void waterPhysics(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	bool vonNeumannNeighborhoodInteraction(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2, VoxelInteractionCondition condition, VoxelInteractionFunction function);
	
	/**
	* Terrain constructor.
	*/
	bool mooreNeighborhoodInteraction(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2, VoxelInteractionCondition condition, VoxelInteractionFunction function);

	/**
	* Terrain constructor.
	*/
	bool waterFall(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	bool waterPush(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	void waterEvaporation(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	void terrainPhysics(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	bool terrainFall(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	void terrainCorrosion(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	void searchForHole(size_t, size_t, size_t);

	/**
	* Terrain constructor.
	*/
	engine::Color waterColor;

	/**
	* Terrain constructor.
	*/
	engine::Color terrainColor;

	/**
	* Terrain constructor.
	*/
	float terrainCorrosionScale;

	/**
	* Terrain constructor.
	*/
	float waterEvaporationScale;
};