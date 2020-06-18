#pragma once

#include "julie/Types.hpp"
#include "julie/Vertex.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class IndexBuffer : boost::noncopyable
{
public:
	IndexBuffer(const index_t* _data, u64 _count) noexcept;
	IndexBuffer(u64 _size) noexcept;
	~IndexBuffer();

	IndexBuffer(IndexBuffer&& _rhs) noexcept;
	IndexBuffer& operator=(IndexBuffer&& _rhs) noexcept;

	void bind() const noexcept;
	void bufferData(const index_t* _data, u64 _count);

	u64 getCount() const noexcept;

private:
	u32 m_id;
	u64 m_size;
	u64 m_count;

	static constexpr u32 k_nullId = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
