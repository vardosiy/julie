#pragma once

#include "renderer/common/Types.hpp"
#include "renderer/common/Vertex.hpp"
#include "renderer/gl_primitives/Buffer.hpp"

#include <boost/noncopyable.hpp>

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class VertexArray
{
public:
	VertexArray(const std::vector<Vertex> & _vertices, const std::vector<u16> & _indices);
	~VertexArray();

	void setLayout() noexcept;

	void bind() const noexcept;

	u32 getVerticesCount() const noexcept { return m_vertexBuffer.getItemsCount(); }
	u32 getIndicesCount() const noexcept { return m_indexBuffer.getItemsCount(); }

private:
	u32 m_id{ 0 };

	Buffer m_vertexBuffer;
	Buffer m_indexBuffer;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
