#include "rendering/objects/Model.hpp"
#include "rendering/common/Vertex.hpp"

#include <array>
#include <memory>
#include <fstream>

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
	for (int i{ 0 }; i < verticesCount; ++i)
	{
		Vertex & vertex = vertices.emplace_back();
		fscanf_s(
			pFile, " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&vertex.pos.x, &vertex.pos.y, &vertex.pos.z,
			&vertex.norm.x, &vertex.norm.y, &vertex.norm.z,
			&vertex.bitangent.x, &vertex.bitangent.y, &vertex.bitangent.z,
			&vertex.tangent.x, &vertex.tangent.y, &vertex.tangent.z,
			&vertex.uv.x, &vertex.uv.y
		);
	}

	int indicesCount{ 0 };
	fscanf_s(pFile, "%*s %d", &indicesCount);

	std::vector<uint16_t> indices(indicesCount);
	for (int i{ 0 }; i < indicesCount; i += 3)
	{
		indices.emplace_back();
		indices.emplace_back();
		indices.emplace_back();
		fscanf_s(
			pFile, " %*d. %hd, %hd, %hd",
			&indices[i + 0], &indices[i + 1], &indices[i + 2]
		);
	}

	fclose(pFile);

	return std::unique_ptr<Model>(new Model(vertices, indices));
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::createRect()
{
	std::vector<Vertex> vertices(4);
	Vertex & vertex1 = vertices.emplace_back();
	vertex1.pos = glm::vec3(-1.0f, -1.0f, 0.0f);
	vertex1.uv = glm::vec2(0.0f, 0.0f);

	Vertex & vertex2 = vertices.emplace_back();
	vertex2.pos = glm::vec3(-1.0f, 1.0f, 0.0f);
	vertex2.uv = glm::vec2(0.0f, 1.0f);

	Vertex & vertex3 = vertices.emplace_back();
	vertex3.pos = glm::vec3(1.0f, -1.0f, 0.0f);
	vertex3.uv = glm::vec2(1.0f, 0.0f);

	Vertex & vertex4 = vertices.emplace_back();
	vertex4.pos = glm::vec3(1.0f, 1.0f, 0.0f);
	vertex4.uv = glm::vec2(1.0f, 1.0f);

	std::vector<uint16_t> indices{ 0, 1, 2, 1, 2, 3 };

	return std::unique_ptr<Model>(new Model(vertices, indices));
}

//-----------------------------------------------------------------------------

Model::~Model()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

//-----------------------------------------------------------------------------

Model::Model(Model && _rhs) noexcept
	: m_vertexBuffer(_rhs.m_vertexBuffer)
	, m_indexBuffer(_rhs.m_indexBuffer)
	, m_verticesCount(_rhs.m_verticesCount)
	, m_indicesCount(_rhs.m_indicesCount)
{
	_rhs.m_vertexBuffer = 0;
	_rhs.m_indexBuffer = 0;
	_rhs.m_verticesCount = 0;
	_rhs.m_indicesCount = 0;
}

//-----------------------------------------------------------------------------

Model & Model::operator =(Model && _rhs) noexcept
{
	std::swap(m_vertexBuffer, _rhs.m_vertexBuffer);
	std::swap(m_indexBuffer, _rhs.m_indexBuffer);
	std::swap(m_verticesCount, _rhs.m_verticesCount);
	std::swap(m_indicesCount, _rhs.m_indicesCount);

	return *this;
}

//-----------------------------------------------------------------------------

void Model::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
}

//-----------------------------------------------------------------------------

Model::Model(const std::vector<Vertex> & _vertices, const std::vector<uint16_t> & _indices)
	: m_verticesCount(_vertices.size())
	, m_indicesCount(_indices.size())
{
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//-----------------------------------------------------------------------------
