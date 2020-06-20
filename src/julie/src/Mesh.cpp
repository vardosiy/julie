#include "julie/Mesh.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<index_t>& _indices) noexcept
	 : m_material(nullptr)
{
	m_vertexArray.bind();
	m_vertexArray.setVertexBuffer(VertexBuffer(_vertices.data(), _vertices.size()));
	m_vertexArray.setIndexBuffer(IndexBuffer(_indices.data(), _indices.size()));

	m_boundingBox = calculateBoundingBox(_vertices);
}

//-----------------------------------------------------------------------------

Mesh::Mesh(Mesh&& _rhs) noexcept
	: m_vertexArray(std::move(_rhs.m_vertexArray))
	, m_boundingBox(_rhs.m_boundingBox)
	, m_material(_rhs.m_material)
{
}

//-----------------------------------------------------------------------------

Mesh& Mesh::operator=(Mesh&& _rhs) noexcept
{
	std::swap(m_vertexArray, _rhs.m_vertexArray);
	std::swap(m_boundingBox, _rhs.m_boundingBox);
	std::swap(m_material, _rhs.m_material);

	return *this;
}

//-----------------------------------------------------------------------------

void Mesh::bind() const
{
	m_vertexArray.bind();
}

//-----------------------------------------------------------------------------

const Material* Mesh::getMaterial() const noexcept
{
	return m_material;
}

//-----------------------------------------------------------------------------

void Mesh::setMaterial(const Material* _material) noexcept
{
	m_material = _material;
}

//-----------------------------------------------------------------------------

u64 Mesh::getIndeciesCount() const noexcept
{
	const IndexBuffer* indexBuffer = m_vertexArray.getIndexBuffer();
	return indexBuffer ? indexBuffer->getCount() : 0;
}

//-----------------------------------------------------------------------------

const aabbf& Mesh::getBoundingBox() const noexcept
{
	return m_boundingBox;
}

//-----------------------------------------------------------------------------

aabbf Mesh::calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept
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

	return aabbf{
		glm::vec3{ leftmost.pos.x, lowest.pos.y, farthest.pos.z },
		glm::vec3{ rightmost.pos.x, highest.pos.y, closest.pos.z }
	};
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
