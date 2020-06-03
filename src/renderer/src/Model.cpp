#include "renderer/Model.hpp"

#include "creation_helpers/ModelCreationHelper.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::loadFromFile(std::string_view _filePath)
{
	return ModelCreationHelper::loadFromFile(_filePath);
}

//-----------------------------------------------------------------------------

std::vector<std::unique_ptr<Model>> Model::load(std::string_view _filePath)
{
	return ModelCreationHelper::load(_filePath);
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
