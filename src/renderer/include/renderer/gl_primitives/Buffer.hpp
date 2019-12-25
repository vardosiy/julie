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
	Buffer(Type _type) noexcept;
	~Buffer();

	template<typename T>
	void bufferData(const std::vector<T> & _data);

	void bind() const noexcept;

	Type	getType() const noexcept		{ return m_type; }
	u32		getItemsCount() const noexcept	{ return m_itemsCount; }

private:
	void bufferData(const void * _data, u32 _size);

	static s32 bufferTypeToGlValue(Type _type);

private:
	u32 m_id;

	Type m_type;
	u32 m_itemsCount;
};

//-----------------------------------------------------------------------------

template<typename T>
void Buffer::bufferData(const std::vector<T> & _data)
{
	m_itemsCount = static_cast<u32>(_data.size());
	bufferData(_data.data(), m_itemsCount * sizeof(T));
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
