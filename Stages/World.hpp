#pragma once

#include <Chunk.hpp>
#include <functional>
#include <random>

/**
* @brief Enum list of voxel types.
*/
enum VoxelType
{
	TERRAIN = 0,
	WATER,
	NUMBER_OF_VOXEL_TYPES
};

/**
* @brief World chunk. It has implemented mechanic of terrain model shaping.
* Have only two types of voxels, the first terrain and the second water.
* Color is attribute.
*/
class World final : public engine::Chunk<engine::Color, NUMBER_OF_VOXEL_TYPES>
{
	/**
	* @brief Function type of condition for singular voxel.
	*/
	using VoxelInteractionCondition = std::function<bool(const engine::Voxel&)>;
	/**
	* @brief Function type of function for singular voxel.
	*/
	using VoxelInteractionFunction = std::function<bool(size_t, size_t, size_t, size_t, size_t, size_t)>;
public:

	/**
	* @brief World constructor.
	*/
	World();
	/**
	* @brief World destructor.
	*/
	~World() = default;

	/**
	* @brief Update the voxels in the chunk.
	* @param dt Time parameter.
	*/
	void update(float dt);

	/**
	* @brief Is raining.
	*/
	bool isRaining;
private:
	/**
	* @brief Create water voxel on passed parameter.
	* @param voxel Reference to voxel.
	*/
	void createWaterVoxel(engine::Voxel& voxel);

	/**
	* @brief Create terrain voxel on passed parameter.
	* @param voxel Reference to voxel.
	*/
	void createTerrainVoxel(engine::Voxel& voxel);

	/**
	* @brief Functionality of physics.
	*/
	void physics();

	/**
	* @brief Rain functionality function.
	*/
	void rain();

	/**
	* @brief Functionality of water physics.
	* @param x X position of the voxel.
	* @param y Y position of the voxel.
	* @param z Z position of the voxel.
	*/
	void waterPhysics(size_t x, size_t y, size_t z);

	/**
	* @brief Von Neuamann neighborhood interaction.
	* @param x1 X position of the main voxel.
	* @param y1 Y position of the main voxel.
	* @param z1 Z position of the main voxel.
	* @param x2 X position of the voxel which interaction refers to.
	* @param y2 Y position of the voxel which interaction refers to.
	* @param z2 Z position of the voxel which interaction refers to.
	* @param condition Function execution condition.
	* @param function Function which will be executed on voxels which meet the condition.
	*/
	bool vonNeumannNeighborhoodInteraction(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2, VoxelInteractionCondition condition, VoxelInteractionFunction function);
	
	/**
	* @brief Moore neighborhood interaction.
	* @param x1 X position of the main voxel.
	* @param y1 Y position of the main voxel.
	* @param z1 Z position of the main voxel.
	* @param x2 X position of the voxel which interaction refers to.
	* @param y2 Y position of the voxel which interaction refers to.
	* @param z2 Z position of the voxel which interaction refers to.
	* @param condition Function execution condition.
	* @param function Function which will be executed on voxels which meet the condition.
	*/
	bool mooreNeighborhoodInteraction(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2, VoxelInteractionCondition condition, VoxelInteractionFunction function);

	/**
	* @brief Functionality of water fall.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	bool waterFalls(size_t x, size_t y, size_t z);

	/**
	* @brief Functionality of water push.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	bool waterPushes(size_t x, size_t y, size_t z);

	/**
	* @brief Functionality of water evaporation.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	void waterEvaporations(size_t x, size_t y, size_t z);

	/**
	* @brief Functionality of terrain physics.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	void terrainPhysics(size_t x, size_t y, size_t z);

	/**
	* @brief Functionality of terrain fall.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	bool terrainFalls(size_t x, size_t y, size_t z);

	/**
	* @brief Functionality of terrain corrosion.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	void terrainCorrosion(size_t x, size_t y, size_t z);

	/**
	* @brief Searching for near hole.
	* @param x1 X position of the voxel.
	* @param y1 Y position of the voxel.
	* @param z1 Z position of the voxel.
	*/
	void searchForHole(size_t x, size_t y, size_t z);

	/**
	* @brief Water voxel color.
	*/
	engine::Color waterColor;

	/**
	* @brief Terrain voxel color.
	*/
	engine::Color terrainColor;

	/**
	* @brief Terrain corrosion scale.
	*/
	float terrainCorrosionScale;

	/**
	* @brief Terrain evaporation scale.
	*/
	float waterEvaporationScale;
};