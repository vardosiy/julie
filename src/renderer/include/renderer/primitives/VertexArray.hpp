#pragma once

#include "renderer/Types.hpp"
#include "renderer/primitives/VertexBuffer.hpp"
#include "renderer/primitives/IndexBuffer.hpp"

#include <boost/noncopyable.hpp>

#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class VertexArray
{
//-----------------------------------------------------------------------------
public:
	VertexArray();
	~VertexArray();

	void bind() const noexcept;

	void setVertexBuffer(std::unique_ptr<VertexBuffer>&& _buffer) noexcept;
	void setIndexBuffer(std::unique_ptr<IndexBuffer>&& _buffer) noexcept;

	VertexBuffer* getVertexBuffer() const noexcept;
	IndexBuffer* getIndexBuffer() const noexcept;

//-----------------------------------------------------------------------------
private:
	void setLayout() noexcept;

//-----------------------------------------------------------------------------
	u32 m_id;

	std::unique_ptr<VertexBuffer> m_vertexBuffer;
	std::unique_ptr<IndexBuffer> m_indexBuffer;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
