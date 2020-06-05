#include "renderer/Mesh.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices) noexcept
{
	m_vertexArray.bind();

	m_vertexArray.setVertexBuffer(std::make_unique<VertexBuffer>(_vertices.data(), _vertices.size()));
	m_vertexArray.setIndexBuffer(std::make_unique<IndexBuffer>(_indices.data(), _indices.size()));

	m_boundingBox = calculateBoundingBox(_vertices);
}

//-----------------------------------------------------------------------------

Mesh::Mesh(Mesh&& _rhs) noexcept
	: m_vertexArray(std::move(_rhs.m_vertexArray))
	, m_boundingBox(_rhs.m_boundingBox)
{
}

//-----------------------------------------------------------------------------

Mesh& Mesh::operator=(Mesh&& _rhs) noexcept
{
	std::swap(m_vertexArray, _rhs.m_vertexArray);
	std::swap(m_boundingBox, _rhs.m_boundingBox);

	return *this;
}

//-----------------------------------------------------------------------------

void Mesh::bind() const
{
	m_vertexArray.bind();
}

//-----------------------------------------------------------------------------

u64 Mesh::getIndeciesCount() const noexcept
{
	const IndexBuffer* indexBuffer = m_vertexArray.getIndexBuffer();
	return indexBuffer ? indexBuffer->getCount() : 0;
}

//-----------------------------------------------------------------------------

const boxf& Mesh::getBoundingBox() const noexcept
{
	return m_boundingBox;
}

//-----------------------------------------------------------------------------

boxf Mesh::calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept
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

	return boxf{
		glm::vec3{ leftmost.pos.x, lowest.pos.y, farthest.pos.z },
		glm::vec3{ rightmost.pos.x, highest.pos.y, closest.pos.z }
	};
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
