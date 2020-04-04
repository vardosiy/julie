#include "renderer/primitives/Buffer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Buffer::Buffer(Type _type) noexcept
	: m_type(bufferTypeToGlValue(_type))
	, m_itemsCount(0)
{
	glGenBuffers(1, &m_id);
}

//-----------------------------------------------------------------------------

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

//-----------------------------------------------------------------------------

void Buffer::bind() const noexcept
{
	glBindBuffer(m_type, m_id);
}

//-----------------------------------------------------------------------------

Buffer::Type Buffer::getType() const noexcept
{
	switch (m_type)
	{
		case GL_ARRAY_BUFFER:			return Type::VertexBuffer;
		case GL_ELEMENT_ARRAY_BUFFER:	return Type::IndexBuffer;
	}

	ASSERT(0);
	return Type::VertexBuffer;
}

//-----------------------------------------------------------------------------

u64 Buffer::getItemsCount() const noexcept
{
	return m_itemsCount;
}

//-----------------------------------------------------------------------------

void Buffer::bufferData(const void* _data, u64 _size)
{
	glBufferData(m_type, _size, _data, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------

s32 Buffer::bufferTypeToGlValue(Type _type)
{
	switch (_type)
	{
		case Type::VertexBuffer:	return GL_ARRAY_BUFFER;
		case Type::IndexBuffer:		return GL_ELEMENT_ARRAY_BUFFER;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
