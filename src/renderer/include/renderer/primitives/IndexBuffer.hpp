#pragma once

#include "renderer/Types.hpp"
#include "renderer/Vertex.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class IndexBuffer : boost::noncopyable
{
public:
	IndexBuffer(const u16* _data, u64 _count) noexcept;
	IndexBuffer(u64 _size) noexcept;
	~IndexBuffer();

	IndexBuffer(IndexBuffer&& _rhs) noexcept;
	IndexBuffer& operator=(IndexBuffer&& _rhs) noexcept;

	void bind() const noexcept;
	void bufferData(const u16* _data, u64 _count);

	u64 getCount() const noexcept;

private:
	u32 m_id;
	u64 m_size;
	u64 m_count;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
