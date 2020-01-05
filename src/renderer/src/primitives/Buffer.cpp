#include "renderer/primitives/Buffer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Buffer::Buffer(Type _type) noexcept
	: m_type(_type)
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
	glBindBuffer(bufferTypeToGlValue(m_type), m_id);
}

//-----------------------------------------------------------------------------

void Buffer::bufferData(const void * _data, u32 _size)
{
	glBufferData(bufferTypeToGlValue(m_type), _size, _data, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------

s32 Buffer::bufferTypeToGlValue(Type _type)
{
	switch (_type)
	{
		case jl::Buffer::Type::VertexBuffer:	return GL_ARRAY_BUFFER;
		case jl::Buffer::Type::IndexBuffer:		return GL_ELEMENT_ARRAY_BUFFER;

		default:
			ASSERT(0);
	}

	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
