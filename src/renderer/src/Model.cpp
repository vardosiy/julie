#include "renderer/Model.hpp"

#include "utils/Utils.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::loadFromFile(std::string_view _filePath)
{
	FILE* pFile = fopen(_filePath.data(), "r");
	if (!pFile)
	{
		return nullptr;
	}

	int verticesCount = 0;
	fscanf_s(pFile, "%*s %d", &verticesCount);
	ASSERTM(verticesCount > 0, "Vercices count has invalid value in file {}", _filePath);

	std::vector<Vertex> vertices(verticesCount);
	for (Vertex& vertex : vertices)
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

Model::Model(const std::vector<Vertex> & _vertices, const std::vector<u16> & _indices)
{
	m_vertexArray.bind();

	m_vertexArray.setVertexBuffer(std::make_unique<VertexBuffer>(_vertices.data(), _vertices.size()));
	m_vertexArray.setIndexBuffer(std::make_unique<IndexBuffer>(_indices.data(), _indices.size()));

	calculateBoundingBox(_vertices);
}

//-----------------------------------------------------------------------------

void Model::bind() const
{
	m_vertexArray.bind();
}

//-----------------------------------------------------------------------------

u64 Model::getIndeciesCount() const noexcept
{
	const IndexBuffer* indexBuffer = m_vertexArray.getIndexBuffer();
	return indexBuffer ? indexBuffer->getCount() : 0;
}

//-----------------------------------------------------------------------------

const boxf& Model::getBoundingBox() const noexcept
{
	return m_boundingBox;
}

//-----------------------------------------------------------------------------

void Model::calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept
{
	auto maxFinder = [&_vertices](auto&& _predicate)
	{
		return std::max_element(_vertices.begin(), _vertices.end(), _predicate);
	};

	const Vertex& leftmost	= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.x > _rhs.pos.x; });
	const Vertex& lowest	= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.y > _rhs.pos.y; });
	const Vertex& farthest	= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.z > _rhs.pos.z; });

	const Vertex& rightmost	= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.x < _rhs.pos.x; });
	const Vertex& highest	= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.y < _rhs.pos.y; });
	const Vertex& closest	= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.z < _rhs.pos.z; });

	m_boundingBox.min = glm::vec3(leftmost.pos.x, lowest.pos.y, farthest.pos.z);
	m_boundingBox.max = glm::vec3(rightmost.pos.x, highest.pos.y, closest.pos.z);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
