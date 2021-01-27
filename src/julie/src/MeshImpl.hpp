#pragma once

#include "julie/core/Types.hpp"
#include "julie/core/Aabb.hpp"
#include "julie/Vertex.hpp"

#include "primitives/VertexArray.hpp"

#include "utils/Noncopyable.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Material;

class MeshImpl : utils::Noncopyable
{
//-----------------------------------------------------------------------------
public:
	MeshImpl(const std::vector<Vertex>& _vertices, const std::vector<u32>& _indices) noexcept;

	MeshImpl(MeshImpl&&) = default;
	MeshImpl& operator=(MeshImpl&&) = default;

//-----------------------------------------------------------------------------
	void bind() const;

	Material* getMaterial() noexcept;
	const Material* getMaterial() const noexcept;
	void setMaterial(Material* _material) noexcept;

	u64 getIndicesCount() const noexcept;
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
