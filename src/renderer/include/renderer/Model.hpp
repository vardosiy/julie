#pragma once

#include "renderer/Types.hpp"
#include "renderer/Vertex.hpp"
#include "renderer/primitives/VertexArray.hpp"

#include <boost/noncopyable.hpp>

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model : boost::noncopyable
{
public:
	Model(const std::vector<Vertex> & _vertices, const std::vector<u16> & _indices);

	void bind() const;

	u32 getVerteciesCount() const noexcept	{ return m_vertexArray.getVerticesCount(); }
	u32 getIndeciesCount() const noexcept	{ return m_vertexArray.getIndicesCount(); }

private:
	VertexArray m_vertexArray;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
