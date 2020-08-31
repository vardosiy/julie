#pragma once

#include "julie/core/Types.hpp"
#include "julie/core/Aabb.hpp"
#include "julie/Vertex.hpp"
#include "julie/Material.hpp"
#include "julie/primitives/VertexArray.hpp"

#include <boost/noncopyable.hpp>

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Material;

class Mesh : boost::noncopyable
{
//-----------------------------------------------------------------------------
public:
	Mesh(const std::vector<Vertex>& _vertices, const std::vector<index_t>& _indices) noexcept;

	Mesh(Mesh&& _rhs) noexcept;
	Mesh& operator=(Mesh&& _rhs) noexcept;

//-----------------------------------------------------------------------------
	void bind() const;

	Material* getMaterial() noexcept;
	const Material* getMaterial() const noexcept;
	void setMaterial(Material* _material) noexcept;

	u64 getIndeciesCount() const noexcept;
	const aabbf& getBoundingBox() const noexcept;

//-----------------------------------------------------------------------------
private:
	static aabbf calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept;

//-----------------------------------------------------------------------------
	VertexArray m_vertexArray;
	aabbf m_boundingBox;

	Material* m_material;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
