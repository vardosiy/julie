#include "julie/primitives/IndexBuffer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

IndexBuffer::IndexBuffer(const index_t* _data, u64 _count) noexcept
	: m_size(_count * sizeof(index_t))
	, m_count(_count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, _data, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------

IndexBuffer::IndexBuffer(u64 _size) noexcept
	: m_size(_size)
	, m_count(0)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, nullptr, GL_DYNAMIC_DRAW);
}

//-----------------------------------------------------------------------------

IndexBuffer::~IndexBuffer()
{
	if (m_id != 0)
	{
		glDeleteBuffers(1, &m_id);
	}
}

//-----------------------------------------------------------------------------

IndexBuffer::IndexBuffer(IndexBuffer&& _rhs) noexcept
	: m_id(_rhs.m_id)
	, m_size(_rhs.m_size)
	, m_count(_rhs.m_count)
{
	_rhs.m_id = 0;
	_rhs.m_size = 0;
	_rhs.m_count = 0;
}

//-----------------------------------------------------------------------------

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);
	std::swap(m_size, _rhs.m_size);
	std::swap(m_count, _rhs.m_count);

	return *this;
}

//-----------------------------------------------------------------------------

void IndexBuffer::bind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

//-----------------------------------------------------------------------------

void IndexBuffer::bufferData(const index_t* _data, u64 _count) noexcept
{
	ASSERT(_count * sizeof(index_t) <= m_size);

	m_count = _count;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _count * sizeof(index_t), _data);
}

//-----------------------------------------------------------------------------

u64 IndexBuffer::getCount() const noexcept
{
	return m_count;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
