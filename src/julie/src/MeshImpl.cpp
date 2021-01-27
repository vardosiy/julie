#include "MeshImpl.hpp"

#include "primitives/VertexArray.hpp"
#include "primitives/IndexBuffer.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

MeshImpl::MeshImpl(const std::vector<Vertex>& _vertices, const std::vector<u32>& _indices) noexcept
	 : m_material(nullptr)
{
	m_vertexArray.bind();
	m_vertexArray.setVertexBuffer(VertexBuffer(_vertices.data(), _vertices.size()));
	m_vertexArray.setIndexBuffer(IndexBuffer(_indices.data(), _indices.size()));

	m_boundingBox = calculateBoundingBox(_vertices);
}

//-----------------------------------------------------------------------------

void MeshImpl::bind() const
{
	m_vertexArray.bind();
}

//-----------------------------------------------------------------------------

Material* MeshImpl::getMaterial() noexcept
{
	return m_material;
}

//-----------------------------------------------------------------------------

const Material* MeshImpl::getMaterial() const noexcept
{
	return m_material;
}
//-----------------------------------------------------------------------------

void MeshImpl::setMaterial(Material* _material) noexcept
{
	m_material = _material;
}

//-----------------------------------------------------------------------------

u64 MeshImpl::getIndicesCount() const noexcept
{
	const IndexBuffer* indexBuffer = m_vertexArray.getIndexBuffer();
	return indexBuffer ? indexBuffer->getCount() : 0;
}

//-----------------------------------------------------------------------------

const aabbf& MeshImpl::getBoundingBox() const noexcept
{
	return m_boundingBox;
}

//-----------------------------------------------------------------------------

aabbf MeshImpl::calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept
{
	auto maxFinder = [&_vertices](int _dimensionIdx)
	{
		return std::max_element(_vertices.begin(), _vertices.end(), [_dimensionIdx](const Vertex& _lhs, const Vertex& _rhs)
		{
			return _lhs.pos[_dimensionIdx] > _rhs.pos[_dimensionIdx];
		});
	};

	const Vertex& leftmost	= *maxFinder(0);
	const Vertex& lowest	= *maxFinder(1);
	const Vertex& farthest	= *maxFinder(2);

	const Vertex& rightmost	= *maxFinder(0);
	const Vertex& highest	= *maxFinder(1);
	const Vertex& closest	= *maxFinder(2);

	return aabbf{
		glm::vec3{ leftmost.pos.x, lowest.pos.y, farthest.pos.z },
		glm::vec3{ rightmost.pos.x, highest.pos.y, closest.pos.z }
	};
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
