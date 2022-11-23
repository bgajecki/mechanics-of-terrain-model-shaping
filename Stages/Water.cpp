#include "Water.hpp"

Water::Water(engine::Mesh* terrain)
	: engine::Mesh(), terrainVertices(terrain->vertices), levelRise(0.0001f), scale(0.0001f)
{
	if (this->terrainVertices.empty())
		return;

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

	this->level = this->minimumLevel = min_y->position.y - this->levelRise;

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

	this->indices.push_back(3);
	this->indices.push_back(2);
	this->indices.push_back(0);

	this->indices.push_back(2);
	this->indices.push_back(1);
	this->indices.push_back(0);
}

void Water::update(const bool isRaining)
{
	
	for (size_t i = 0u; i < this->terrainVertices.size(); i++)
	{
		float difference = this->level - this->terrainVertices[i].position.y;

		if (difference > 0.0f)
		{
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

			for (size_t j = 0u; j < sameVertices.size(); j++)
			{
				sameVertices[j]->position += -normal * difference * this->scale;
			}
		}
	}

	for (size_t i = 0u; i < this->indices.size(); i+=3u)
	{
		engine::MeshVertex a = this->vertices[this->indices[i]];
		engine::MeshVertex b = this->vertices[this->indices[i+1]];
		engine::MeshVertex c = this->vertices[this->indices[i+2]];
		engine::Position ab = b.position - a.position;
		engine::Position bc = b.position - a.position;
		a.normal = b.normal = c.normal = glm::normalize(glm::cross(ab, bc));
	}

	this->level += isRaining ? this->levelRise : -this->levelRise;
	if(this->level > this->minimumLevel)
		for (auto& vertex : this->vertices)
			vertex.position.y = this->level;

}
