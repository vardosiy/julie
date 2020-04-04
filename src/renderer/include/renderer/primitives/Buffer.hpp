#pragma once

#include "renderer/Types.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Buffer
{
//-----------------------------------------------------------------------------
public:
	enum class Type{ VertexBuffer, IndexBuffer };

//-----------------------------------------------------------------------------
	Buffer(Type _type) noexcept;
	~Buffer();

	template<typename T>
	void bufferData(const std::vector<T>& _data);

	void bind() const noexcept;

	u64 getItemsCount() const noexcept;
	Type getType() const noexcept;

//-----------------------------------------------------------------------------
private:
	void bufferData(const void* _data, u64 _size);

	static s32 bufferTypeToGlValue(Type _type);

//-----------------------------------------------------------------------------
	u32 m_id;
	s32 m_type;

	u64 m_itemsCount;
};

//-----------------------------------------------------------------------------

template<typename T>
inline void Buffer::bufferData(const std::vector<T>& _data)
{
	m_itemsCount = static_cast<u64>(_data.size());
	bufferData(_data.data(), m_itemsCount * sizeof(T));
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
