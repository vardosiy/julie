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
	Model(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices);

	void bind() const;

	u32 getVerteciesCount() const noexcept;
	u32 getIndeciesCount() const noexcept;

	const boxf& getBoundingBox() const noexcept;

private:
	VertexArray m_vertexArray;

	boxf m_boundingBox;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
