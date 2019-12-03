#pragma once

#include "renderer/common/Types.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Buffer
{
public:
	enum class Type{ VertexBuffer, IndexBuffer };

public:
	template<typename T>
	Buffer(Type _type, const std::vector<T> & _data);
	~Buffer();

	void bind() const noexcept;

	Type getType() const noexcept				{ return m_type; }
	u32 getBufferedItemsCount() const noexcept	{ return m_itemsCount; }

private:
	void bufferData(const void * _data, u32 _size);

private:
	u32 m_id;

	Type m_type;
	u32 m_itemsCount;
};

//-----------------------------------------------------------------------------

template<typename T>
Buffer::Buffer(Type _type, const std::vector<T> & _data)
	: m_id(0)
	, m_type(_type)
	, m_itemsCount(static_cast<u32>(_data.size()))
{
	bufferData(_data.data(), m_itemsCount * sizeof(T));
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
