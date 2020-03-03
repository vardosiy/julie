#include "renderer/Model.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Model::Model(const std::vector<Vertex> & _vertices, const std::vector<u16> & _indices)
	: m_vertexArray(_vertices, _indices)
{
	calculateBoundingBox(_vertices);
}

//-----------------------------------------------------------------------------

void Model::bind() const
{
	m_vertexArray.bind();
}

//-----------------------------------------------------------------------------

u32 Model::getVerteciesCount() const noexcept
{
	return m_vertexArray.getVerticesCount();
}

//-----------------------------------------------------------------------------

u32 Model::getIndeciesCount() const noexcept
{
	return m_vertexArray.getIndicesCount();
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

	const Vertex& rightmost		= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.x < _rhs.pos.x; });
	const Vertex& leftmost		= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.x > _rhs.pos.x; });
	const Vertex& highest		= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.y < _rhs.pos.y; });
	const Vertex& lowest		= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.y > _rhs.pos.y; });
	const Vertex& closest		= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.z < _rhs.pos.z; });
	const Vertex& farthest		= *maxFinder([](const Vertex& _lhs, const Vertex& _rhs) { return _lhs.pos.z > _rhs.pos.z; });

	m_boundingBox.frontRect.topLeft		= glm::vec3(rightmost.pos.x, highest.pos.y, farthest.pos.z);
	m_boundingBox.frontRect.bottomRight	= glm::vec3(leftmost.pos.x, lowest.pos.y, farthest.pos.z);
	m_boundingBox.backRect.topLeft		= glm::vec3(rightmost.pos.x, highest.pos.y, closest.pos.z);
	m_boundingBox.backRect.bottomRight	= glm::vec3(leftmost.pos.x, lowest.pos.y, closest.pos.z);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
