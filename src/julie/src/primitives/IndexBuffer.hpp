#pragma once

#include "julie/core/Types.hpp"

#include "utils/Noncopyable.hpp"

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

class IndexBuffer : utils::Noncopyable
{
public:
	IndexBuffer(const u32* _data, u64 _count) noexcept;
	IndexBuffer(u64 _size) noexcept;
	~IndexBuffer();

	IndexBuffer(IndexBuffer&& _rhs) noexcept;
	IndexBuffer& operator=(IndexBuffer&& _rhs) noexcept;

	void bind() const noexcept;
	void bufferData(const u32* _data, u64 _count);

	u64 getCount() const noexcept;

private:
	u32 m_id;
	u64 m_size;
	u64 m_count;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
