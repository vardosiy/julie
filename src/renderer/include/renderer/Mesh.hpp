#pragma once

#include "renderer/Types.hpp"
#include "renderer/Vertex.hpp"
#include "renderer/primitives/VertexArray.hpp"

#include <boost/noncopyable.hpp>

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Material;

class Mesh : boost::noncopyable
{
public:
	Mesh(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices) noexcept;

	Mesh(Mesh&& _rhs) noexcept;
	Mesh& operator=(Mesh&& _rhs) noexcept;

	void bind() const;

	const Material* getMaterial() const noexcept;
	void setMaterial(const Material* _material) noexcept;

	u64 getIndeciesCount() const noexcept;
	const boxf& getBoundingBox() const noexcept;

private:
	static boxf calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept;

	VertexArray m_vertexArray;
	boxf m_boundingBox;

	const Material* m_material;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
