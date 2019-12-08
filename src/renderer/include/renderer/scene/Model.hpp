#pragma once

#include "renderer/common/Types.hpp"
#include "renderer/common/Vertex.hpp"
#include "renderer/gl_primitives/VertexArray.hpp"

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
	static std::unique_ptr<Model> createRect(const glm::vec3 & _pos, const glm::vec2 & _size); // _pos => bottom-left coord

public:
	void bind() const;

	u32 getVerteciesCount() const noexcept { return m_vertexArray.getVerticesCount(); }
	u32 getIndeciesCount() const noexcept { return m_vertexArray.getIndicesCount(); }

private:
	Model(const std::vector<Vertex> & _vertices, const std::vector<u16> & _indices);

private:
	VertexArray m_vertexArray;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
