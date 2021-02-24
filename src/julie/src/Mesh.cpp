#include "julie/Mesh.hpp"

#include "MeshImpl.hpp"

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<u32>& _indices) noexcept
	: m_impl(_vertices, _indices)
{
}

Mesh::~Mesh() noexcept = default;

Mesh::Mesh(Mesh&& _rhs) noexcept
	: m_impl(std::move(*_rhs.m_impl))
{
}

Mesh& Mesh::operator=(Mesh&& _rhs) noexcept
{
	*m_impl = std::move(*_rhs.m_impl);
	return *this;
}

//-----------------------------------------------------------------------------

void Mesh::bind() const
{
	m_impl->bind();
}

//-----------------------------------------------------------------------------

Material* Mesh::getMaterial() noexcept
{
	return m_impl->getMaterial();
}

const Material* Mesh::getMaterial() const noexcept
{
	return m_impl->getMaterial();
}

void Mesh::setMaterial(Material* _material) noexcept
{
	m_impl->setMaterial(_material);
}

//-----------------------------------------------------------------------------

u64 Mesh::getIndicesCount() const noexcept
{
	return m_impl->getIndicesCount();
}

const aabbf& Mesh::getBoundingBox() const noexcept
{
	return m_impl->getBoundingBox();
}

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
