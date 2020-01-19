#include "renderer/loaders/ModelsFactory.hpp"

#include "renderer/Vertex.hpp"
#include "renderer/Model.hpp"

#include "utils/Assert.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelsFactory::loadFromFile(std::string_view _filePath)
{
	FILE* pFile = fopen(_filePath.data(), "r");
	if (!pFile)
	{
		return nullptr;
	}

	s32 verticesCount = 0;
	fscanf_s(pFile, "%*s %d", &verticesCount);
	ASSERTM(verticesCount > 0, "Vercices count has invalid value in file {}", _filePath);

	std::vector<Vertex> vertices(verticesCount);
	for (Vertex & vertex : vertices)
	{
		fscanf_s(
			pFile, " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&vertex.pos.x, &vertex.pos.y, &vertex.pos.z,
			&vertex.norm.x, &vertex.norm.y, &vertex.norm.z,
			&vertex.bitangent.x, &vertex.bitangent.y, &vertex.bitangent.z,
			&vertex.tangent.x, &vertex.tangent.y, &vertex.tangent.z,
			&vertex.uv.x, &vertex.uv.y
		);
	}

	s32 indicesCount = 0;
	fscanf_s(pFile, "%*s %d", &indicesCount);
	ASSERTM(indicesCount > 0, "Vercices count has invalid value in file {}", _filePath);

	std::vector<u16> indices(indicesCount);
	for (s32 i = 0; i < indicesCount; i += 3)
	{
		fscanf_s(
			pFile, " %*d. %hd, %hd, %hd",
			&indices[i], &indices[i + 1], &indices[i + 2]
		);
	}

	fclose(pFile);

	return std::make_unique<Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelsFactory::createRect()
{
	std::vector<Vertex> vertices(4);
	vertices[0].pos = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices[1].pos = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices[2].pos = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices[3].pos = glm::vec3(1.0f, 1.0f, 0.0f);

	vertices[0].uv = glm::vec2(0.0f, 0.0f);
	vertices[1].uv = glm::vec2(0.0f, 1.0f);
	vertices[2].uv = glm::vec2(1.0f, 0.0f);
	vertices[3].uv = glm::vec2(1.0f, 1.0f);

	std::vector<u16> indices = { 0, 1, 2, 1, 2, 3 };
	return std::make_unique<Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
