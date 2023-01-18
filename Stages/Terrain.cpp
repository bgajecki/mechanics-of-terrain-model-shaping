#include "Terrain.hpp"

Terrain::Terrain()
	: engine::Mesh()
{
	this->loadObj("./objects/terrain.obj");
	this->primitivesType = GL_PATCHES;
}
