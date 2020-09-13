#pragma once

#include "julie/core/Types.hpp"
#include "julie/primitives/VertexBuffer.hpp"
#include "julie/primitives/IndexBuffer.hpp"

#include "utils/Noncopyable.hpp"

#include <optional>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class VertexArray : utils::Noncopyable
{
//-----------------------------------------------------------------------------
public:
	VertexArray() noexcept;
	~VertexArray();

	VertexArray(VertexArray&& _rhs) noexcept;
	VertexArray& operator=(VertexArray&& _rhs) noexcept;

	void bind() const noexcept;

	VertexBuffer* getVertexBuffer() noexcept;
	IndexBuffer* getIndexBuffer() noexcept;

	const VertexBuffer* getVertexBuffer() const noexcept;
	const IndexBuffer* getIndexBuffer() const noexcept;

	void setVertexBuffer(VertexBuffer&& _buffer) noexcept;
	void setIndexBuffer(IndexBuffer&& _buffer) noexcept;

//-----------------------------------------------------------------------------
private:
	void setupLayout() noexcept;

//-----------------------------------------------------------------------------
	u32 m_id;

	std::optional<VertexBuffer> m_vertexBuffer;
	std::optional<IndexBuffer> m_indexBuffer;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
