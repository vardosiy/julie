#pragma once

#include "renderer/Types.hpp"
#include "renderer/Vertex.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class VertexBuffer : boost::noncopyable
{
public:
	VertexBuffer(const Vertex* _data, u64 _count) noexcept;
	VertexBuffer(u64 _size) noexcept;
	~VertexBuffer();

	VertexBuffer(VertexBuffer&& _rhs) noexcept;
	VertexBuffer& operator=(VertexBuffer&& _rhs) noexcept;

	void bind() const noexcept;
	void bufferData(const Vertex* _data, u64 _count, u64 _offset) noexcept;

	u64 getSize() const noexcept;

private:
	u32 m_id;
	u64 m_size;

	static constexpr u32 k_nullId = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
