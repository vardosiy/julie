#include "renderer/primitives/VertexArray.hpp"

#include <glad/glad.h>

#include <array>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

VertexArray::VertexArray(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices)
	: m_id(0)
	, m_vertexBuffer(Buffer::Type::VertexBuffer)
	, m_indexBuffer(Buffer::Type::IndexBuffer)
{
	glGenVertexArrays(1, &m_id);
	bind();

	m_vertexBuffer.bind();
	m_vertexBuffer.bufferData(_vertices);
	m_indexBuffer.bind();
	m_indexBuffer.bufferData(_indices);

	setLayout();
}

//-----------------------------------------------------------------------------

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

//-----------------------------------------------------------------------------

void VertexArray::bind() const noexcept
{
	glBindVertexArray(m_id);
}

//-----------------------------------------------------------------------------

u32 VertexArray::getVerticesCount() const noexcept
{
	return m_vertexBuffer.getItemsCount();
}

//-----------------------------------------------------------------------------

u32 VertexArray::getIndicesCount() const noexcept
{
	return m_indexBuffer.getItemsCount();
}

//-----------------------------------------------------------------------------

void VertexArray::setLayout() noexcept
{
	constexpr u32 k_vertexAttribsCount = 5;
	constexpr std::array<u32, k_vertexAttribsCount> sizes = { 3, 2, 3, 3, 3 };

	const float * offset = nullptr;
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
