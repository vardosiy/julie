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
//-----------------------------------------------------------------------------
public:
	Model(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices);

	void bind() const;

	u64 getVerteciesCount() const noexcept;
	u64 getIndeciesCount() const noexcept;

	const boxf& getBoundingBox() const noexcept;

//-----------------------------------------------------------------------------
private:
	void calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept;

//-----------------------------------------------------------------------------
	VertexArray m_vertexArray;
	boxf m_boundingBox;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
