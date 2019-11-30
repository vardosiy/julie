#include "renderer/gl_primitives/Buffer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

uint32_t convertToGlType(Buffer::Type _type)
{
	switch (_type)
	{
		case Buffer::Type::VertexBuffer:	return GL_ARRAY_BUFFER;
		case Buffer::Type::IndexBuffer:		return GL_ELEMENT_ARRAY_BUFFER;
	}

	ASSERT(false, "Unhandlad buffer type");
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

//-----------------------------------------------------------------------------

void Buffer::bind() const noexcept
{
	glBindBuffer(details::convertToGlType(m_type), m_id);
}

//-----------------------------------------------------------------------------

void Buffer::bufferData(const void * _data, int _size)
{
	const uint32_t glBufferType = details::convertToGlType(m_type);

	glGenBuffers(1, &m_id);
	glBindBuffer(glBufferType, m_id);
	glBufferData(glBufferType, _size, _data, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------
