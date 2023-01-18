#include "Water.hpp"

Water::Water(engine::Mesh* terrain)
	: engine::Mesh(), terrainVertices(terrain->vertices), terrainVerticesCopy(terrain->vertices), levelRise(0.0001f), scale(0.0001f), level(0.0f), minimumLevel(0.0f), maxChange(0.3f)
{
	if (this->terrainVertices.empty())
		return;

	this->primitivesType = GL_PATCHES;

	auto [min_x, max_x] = std::minmax_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::MeshVertex& v1, const engine::MeshVertex& v2) -> bool
	{
		return v1.position.x < v2.position.x;
	});

	auto [min_z, max_z] = std::minmax_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::MeshVertex& v1, const engine::MeshVertex& v2) -> bool
	{
		return v1.position.z < v2.position.z;
	});

	auto min_y = std::min_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::MeshVertex& v1, const engine::MeshVertex& v2) -> bool
	{
		return v1.position.y < v2.position.y;
	});
	// Set water level.
	this->level = this->minimumLevel = min_y->position.y - this->levelRise;

	// Create water model based on terrain model.
	engine::MeshVertex vertex;
	vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex.position.x = min_x->position.x;
	vertex.position.z = min_z->position.z;
	vertex.position.y = this->level;
	vertex.attribute = glm::vec2(0.0f, 0.0f);
	this->vertices.push_back(vertex);
	vertex.position.x = max_x->position.x;
	vertex.position.z = min_z->position.z;
	vertex.position.y = this->level;
	vertex.attribute = glm::vec2(1.0f, 0.0f);
	this->vertices.push_back(vertex);
	vertex.position.x = max_x->position.x;
	vertex.position.z = max_z->position.z;
	vertex.position.y = this->level;
	vertex.attribute = glm::vec2(1.0f, 1.0f);
	this->vertices.push_back(vertex);
	vertex.position.x = min_x->position.x;
	vertex.position.z = max_z->position.z;
	vertex.position.y = this->level;
	vertex.attribute = glm::vec2(0.0f, 1.0f);
	this->vertices.push_back(vertex);
	// Create indices for patch.
	this->indices.push_back(3);
	this->indices.push_back(2);
	this->indices.push_back(1);
	this->indices.push_back(0);

	/*
	// Create indices for triangles.
	this->indices.push_back(3);
	this->indices.push_back(2);
	this->indices.push_back(0);

	this->indices.push_back(2);
	this->indices.push_back(1);
	this->indices.push_back(0);
	*/
}

void Water::update(bool isRaining)
{
	// For each vertex of the terrain...
	for (size_t i = 0u; i < this->terrainVertices.size(); i++)
	{
		float difference = this->level - this->terrainVertices[i].position.y;
		// Check is terrain vertex is under water model.
		if (difference > 0.0f)
		{
			float change = glm::abs(glm::distance(this->terrainVerticesCopy[i].position, this->terrainVertices[i].position));
			// Limit the corrosion.
			if (this->maxChange > change)
			{
				// Get all the patches this vertex belongs to and calc average normal vector.
				std::vector<engine::MeshVertex*> sameVertices;
				engine::Normal normal = glm::vec3(0.0f, 0.0f, 0.0f);

				for (size_t j = 0u; j < this->terrainVertices.size(); j++)
				{
					if (this->terrainVertices[i].position == this->terrainVertices[j].position)
					{
						sameVertices.push_back(&this->terrainVertices[j]);
						normal += this->terrainVertices[j].normal;
					}
				}
				normal /= sameVertices.size();
				normal.y *= 0.5f;
				// Change vertex position for all patches.
				for (size_t j = 0u; j < sameVertices.size(); j++)
				{
					sameVertices[j]->position += -normal * difference * this->scale;
				}
			}
		}
	}
	/*
	for (size_t i = 0u; i < this->terrainVertices.size(); i+=3u)
	{
		engine::MeshVertex& a = this->terrainVertices[i];
		engine::MeshVertex& b = this->terrainVertices[i+1];
		engine::MeshVertex& c = this->terrainVertices[i+2];
		engine::Position ab = b.position - a.position;
		engine::Position bc = b.position - a.position;
		a.normal = b.normal = c.normal = d.normal = glm::normalize(glm::cross(ab, bc));
	}
	*/
	// Get the lowest vertex of the terrain along the Y axis.
	auto min_y = std::min_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::MeshVertex& v1, const engine::MeshVertex& v2) -> bool
	{
		return v1.position.y < v2.position.y;
	});
	this->minimumLevel = min_y->position.y - this->levelRise;
	// When it rains, the water level rises. When not, the water level drops.
	if (isRaining)
		this->level += this->levelRise;
	else
		if(this->level != this->minimumLevel)
			this->level -= this->levelRise;
	// Update water model vertices to the water level.
	if(this->level > this->minimumLevel)
		for (auto& vertex : this->vertices)
			vertex.position.y = this->level;
}
