#pragma once

#include <cstdint>
#include <vector>

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
	int getBufferedItemsCount() const noexcept	{ return m_itemsCount; }

private:
	void bufferData(const void * _data, int _size);

private:
	uint32_t m_id;

	Type m_type;
	int m_itemsCount;
};

//-----------------------------------------------------------------------------

template<typename T>
Buffer::Buffer(Type _type, const std::vector<T> & _data)
	: m_id(0)
	, m_type(_type)
	, m_itemsCount(_data.size())
{
	bufferData(_data.data(), _data.size() * sizeof(T));
}

//-----------------------------------------------------------------------------
