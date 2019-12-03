#pragma once

#include "renderer/common/Types.hpp"
#include "renderer/common/Vertex.hpp"
#include "renderer/gl_primitives/Buffer.hpp"

#include <glm/glm.hpp>

#include <boost/noncopyable.hpp>

#include <string_view>
#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model : boost::noncopyable
{
public:
	static std::unique_ptr<Model> create(std::string_view _filePath);
	static std::unique_ptr<Model> createRect(const glm::vec3 & _pos, const glm::vec2 & _size); // bottom-left and size

public:
	void bind() const;

	u32 getVerteciesCount() const noexcept	{ return m_vertexBuffer.getBufferedItemsCount(); }
	u32 getIndeciesCount() const noexcept	{ return m_indexBuffer.getBufferedItemsCount(); }

private:
	Model(const std::vector<Vertex> & _vertices, const std::vector<uint16_t> & _indices);

private:
	Buffer m_vertexBuffer;
	Buffer m_indexBuffer;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
