#include "julie/primitives/VertexArray.hpp"
#include "julie/Vertex.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>
#include <array>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

VertexArray::VertexArray() noexcept
{
	glGenVertexArrays(1, &m_id);
}

//-----------------------------------------------------------------------------

VertexArray::~VertexArray()
{
	if (m_id != 0)
	{
		glDeleteVertexArrays(1, &m_id);
	}
}

//-----------------------------------------------------------------------------

VertexArray::VertexArray(VertexArray&& _rhs) noexcept
	: m_id(_rhs.m_id)
	, m_vertexBuffer(std::move(_rhs.m_vertexBuffer))
	, m_indexBuffer(std::move(_rhs.m_indexBuffer))
{
	_rhs.m_id = 0;
	_rhs.m_vertexBuffer.reset();
	_rhs.m_indexBuffer.reset();
}

//-----------------------------------------------------------------------------

VertexArray& VertexArray::operator=(VertexArray&& _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);
	std::swap(m_vertexBuffer, _rhs.m_vertexBuffer);
	std::swap(m_indexBuffer, _rhs.m_indexBuffer);

	return *this;
}

//-----------------------------------------------------------------------------

void VertexArray::bind() const noexcept
{
	glBindVertexArray(m_id);
}

//-----------------------------------------------------------------------------

VertexBuffer* VertexArray::getVertexBuffer() noexcept
{
	return m_vertexBuffer.has_value() ? &m_vertexBuffer.value() : nullptr;
}

//-----------------------------------------------------------------------------

IndexBuffer* VertexArray::getIndexBuffer() noexcept
{
	return m_indexBuffer.has_value() ? &m_indexBuffer.value() : nullptr;
}

//-----------------------------------------------------------------------------

const VertexBuffer* VertexArray::getVertexBuffer() const noexcept
{
	return m_vertexBuffer.has_value() ? &m_vertexBuffer.value() : nullptr;
}

//-----------------------------------------------------------------------------

const IndexBuffer* VertexArray::getIndexBuffer() const noexcept
{
	return m_indexBuffer.has_value() ? &m_indexBuffer.value() : nullptr;
}

//-----------------------------------------------------------------------------

void VertexArray::setVertexBuffer(VertexBuffer&& _buffer) noexcept
{
	m_vertexBuffer = std::move(_buffer);

	bind();
	m_vertexBuffer->bind();
	setupLayout();
}

//-----------------------------------------------------------------------------

void VertexArray::setIndexBuffer(IndexBuffer&& _buffer) noexcept
{
	m_indexBuffer = std::move(_buffer);

	bind();
	m_indexBuffer->bind();
}

//-----------------------------------------------------------------------------

void VertexArray::setupLayout() noexcept
{
	constexpr u32 k_vertexAttribsCount = 5;
	constexpr std::array<u32, k_vertexAttribsCount> sizes = { 3, 2, 3, 3, 3 };

	const float* offset = nullptr;
	for (u32 i = 0; i < k_vertexAttribsCount; ++i)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, sizes[i], GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);

		offset += sizes[i];
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
