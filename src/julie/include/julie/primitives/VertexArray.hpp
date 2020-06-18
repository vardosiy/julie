#pragma once

#include "julie/Types.hpp"
#include "julie/primitives/VertexBuffer.hpp"
#include "julie/primitives/IndexBuffer.hpp"

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class VertexArray
{
//-----------------------------------------------------------------------------
public:
	VertexArray() noexcept;
	~VertexArray();

	VertexArray(VertexArray&& _rhs) noexcept;
	VertexArray& operator= (VertexArray&& _rhs) noexcept;

	void bind() const noexcept;

	void setVertexBuffer(VertexBuffer&& _buffer) noexcept;
	void setIndexBuffer(IndexBuffer&& _buffer) noexcept;

	VertexBuffer* getVertexBuffer() noexcept;
	IndexBuffer* getIndexBuffer() noexcept;

	const VertexBuffer* getVertexBuffer() const noexcept;
	const IndexBuffer* getIndexBuffer() const noexcept;

//-----------------------------------------------------------------------------
private:
	void setLayout() noexcept;

//-----------------------------------------------------------------------------
	u32 m_id;

	boost::optional<VertexBuffer> m_vertexBuffer;
	boost::optional<IndexBuffer> m_indexBuffer;

	static constexpr u32 k_nullId = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
