#include "julie/primitives/VertexBuffer.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

VertexBuffer::VertexBuffer(const Vertex* _data, u64 _count) noexcept
	: m_size(_count * sizeof(Vertex))
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, m_size, _data, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------

VertexBuffer::VertexBuffer(u64 _size) noexcept
	: m_size(_size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, m_size, nullptr, GL_DYNAMIC_DRAW);
}

//-----------------------------------------------------------------------------

VertexBuffer::~VertexBuffer()
{
	if (m_id != 0)
	{
		glDeleteBuffers(1, &m_id);
	}
}

//-----------------------------------------------------------------------------

VertexBuffer::VertexBuffer(VertexBuffer&& _rhs) noexcept
	: m_id(_rhs.m_id)
	, m_size(_rhs.m_size)
{
	_rhs.m_id = 0;
	_rhs.m_size = 0;
}

//-----------------------------------------------------------------------------

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);
	std::swap(m_size, _rhs.m_size);

	return *this;
}

//-----------------------------------------------------------------------------

void VertexBuffer::bind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

//-----------------------------------------------------------------------------

void VertexBuffer::bufferData(const Vertex* _data, u64 _count, u64 _offset) noexcept
{
	ASSERT(_count * sizeof(Vertex) + _offset <= m_size);

	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferSubData(GL_ARRAY_BUFFER, _offset, _count * sizeof(Vertex), _data);
}

//-----------------------------------------------------------------------------

u64 VertexBuffer::getSize() const noexcept
{
	return m_size;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
