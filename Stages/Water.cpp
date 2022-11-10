#include "Water.hpp"
#include "Water.hpp"

Water::Water(engine::Mesh* terrain)
	: engine::Mesh(), terrainVertices(terrain->vertices), levelRise(0.0001f), scale(0.0001f)
{
	if (this->terrainVertices.empty())
		return;

	auto [min_x, max_x] = std::minmax_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::Vertex& v1, const engine::Vertex& v2) -> bool
	{
		return v1.position.x < v2.position.x;
	});

	auto [min_z, max_z] = std::minmax_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::Vertex& v1, const engine::Vertex& v2) -> bool
	{
		return v1.position.z < v2.position.z;
	});

	auto min_y = std::min_element(this->terrainVertices.begin(), this->terrainVertices.end(), [](const engine::Vertex& v1, const engine::Vertex& v2) -> bool
	{
		return v1.position.y < v2.position.y;
	});

	this->level = this->minimumLevel = min_y->position.y - this->levelRise;

	engine::Vertex vertex;
	vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex.position.x = min_x->position.x;
	vertex.position.z = min_z->position.z;
	vertex.position.y = this->level;
	vertex.textureCoordinate = glm::vec2(0.0f, 0.0f);
	this->vertices.push_back(vertex);
	vertex.position.x = max_x->position.x;
	vertex.position.z = min_z->position.z;
	vertex.position.y = this->level;
	vertex.textureCoordinate = glm::vec2(1.0f, 0.0f);
	this->vertices.push_back(vertex);
	vertex.position.x = max_x->position.x;
	vertex.position.z = max_z->position.z;
	vertex.position.y = this->level;
	vertex.textureCoordinate = glm::vec2(1.0f, 1.0f);
	this->vertices.push_back(vertex);
	vertex.position.x = min_x->position.x;
	vertex.position.z = max_z->position.z;
	vertex.position.y = this->level;
	vertex.textureCoordinate = glm::vec2(0.0f, 1.0f);
	this->vertices.push_back(vertex);

	this->indices.push_back(0);
	this->indices.push_back(1);
	this->indices.push_back(2);

	this->indices.push_back(0);
	this->indices.push_back(2);
	this->indices.push_back(3);
	
	std::reverse(this->indices.begin(), this->indices.end());
}

void Water::update(const bool isRaining)
{
	
	for (unsigned i = 0u; i < this->terrainVertices.size(); i++)
	{
		float difference = this->level - this->terrainVertices[i].position.y;

		if (difference > 0.0f)
		{
			std::vector<engine::Vertex*> sameVertices;
			engine::Normal normal = glm::vec3(0.0f, 0.0f, 0.0f);

			for (unsigned j = 0; j < this->terrainVertices.size(); j++)
			{
				if (this->terrainVertices[i].position == this->terrainVertices[j].position)
				{
					sameVertices.push_back(&this->terrainVertices[j]);
					normal += this->terrainVertices[j].normal;
				}
			}
			normal /= sameVertices.size();
			normal.y *= 0.5;

			for (unsigned j = 0u; j < sameVertices.size(); j++)
			{
				sameVertices[j]->position += -normal * difference * this->scale;
			}


			// TODO: Recalculate normals

		}
	}
	this->level += isRaining ? this->levelRise : -this->levelRise;
	if(this->level > this->minimumLevel)
		for (auto& vertex : this->vertices)
			vertex.position.y = this->level;

}
