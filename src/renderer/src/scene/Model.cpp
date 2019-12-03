#include "renderer/scene/Model.hpp"
#include "renderer/common/Vertex.hpp"

#include <glad/glad.h>

#include <array>
#include <memory>
#include <fstream>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::create(std::string_view _filePath)
{
	FILE * pFile = fopen(_filePath.data(), "r");
	if (!pFile)
	{
		return nullptr;
	}

	int verticesCount{ 0 };
	fscanf_s(pFile, "%*s %d", &verticesCount);

	std::vector<Vertex> vertices(verticesCount);
	for (auto & vertex : vertices)
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

	s32 indicesCount{ 0 };
	fscanf_s(pFile, "%*s %d", &indicesCount);

	std::vector<u16> indices(indicesCount);
	for (s32 i{ 0 }; i < indicesCount; i += 3)
	{
		fscanf_s(
			pFile, " %*d. %hd, %hd, %hd",
			&indices[i], &indices[i + 1], &indices[i + 2]
		);
	}

	fclose(pFile);

	return std::unique_ptr<Model>(new Model(vertices, indices));
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::createRect(const glm::vec3 & _pos, const glm::vec2 & _size)
{
	std::vector<Vertex> vertices(4);
	vertices[0].pos = _pos;
	vertices[1].pos = _pos + glm::vec3{ 0.0f, _size.y, 0.0f };
	vertices[2].pos = _pos + glm::vec3{ _size.x, 0.0f, 0.0f };
	vertices[3].pos = _pos + glm::vec3{ _size.x, _size.y, 0.0f };

	vertices[0].uv = glm::vec2{ 0.0f, 0.0f };
	vertices[1].uv = glm::vec2{ 0.0f, 1.0f };
	vertices[2].uv = glm::vec2{ 1.0f, 0.0f };
	vertices[3].uv = glm::vec2{ 1.0f, 1.0f };

	std::vector<uint16_t> indices{ 0, 1, 2, 1, 2, 3 };
	return std::unique_ptr<Model>(new Model(vertices, indices));
}

//-----------------------------------------------------------------------------

void Model::bind() const
{
	m_vertexBuffer.bind();
	m_indexBuffer.bind();
}

//-----------------------------------------------------------------------------

Model::Model(const std::vector<Vertex> & _vertices, const std::vector<uint16_t> & _indices)
	: m_vertexBuffer(Buffer::Type::VertexBuffer, _vertices)
	, m_indexBuffer(Buffer::Type::IndexBuffer, _indices)
{
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
