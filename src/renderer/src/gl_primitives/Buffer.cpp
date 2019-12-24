#include "renderer/gl_primitives/Buffer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

jl::u32 convertToGlType(jl::Buffer::Type _type)
{
	switch (_type)
	{
		case jl::Buffer::Type::VertexBuffer:	return GL_ARRAY_BUFFER;
		case jl::Buffer::Type::IndexBuffer:		return GL_ELEMENT_ARRAY_BUFFER;
	}

	ASSERT(false, "Unhandlad buffer type");
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace details

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

Buffer::Buffer(Buffer && _rhs) noexcept
	: m_id(_rhs.m_id)
	, m_type(_rhs.m_type)
	, m_itemsCount(_rhs.m_itemsCount)
{
	_rhs.m_id = 0;
	_rhs.m_type = Type::VertexBuffer;
	_rhs.m_itemsCount = 0;
}

//-----------------------------------------------------------------------------

Buffer & Buffer::operator=(Buffer && _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);
	std::swap(m_type, _rhs.m_type);
	std::swap(m_itemsCount, _rhs.m_itemsCount);

	return *this;
}

//-----------------------------------------------------------------------------

void Buffer::bind() const noexcept
{
	glBindBuffer(details::convertToGlType(m_type), m_id);
}

//-----------------------------------------------------------------------------

void Buffer::bufferData(const void * _data, u32 _size)
{
	glBufferData(details::convertToGlType(m_type), _size, _data, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
