#pragma once

#include "renderer/Types.hpp"
#include "renderer/Vertex.hpp"
#include "renderer/primitives/VertexArray.hpp"

#include <boost/noncopyable.hpp>

#include <vector>
#include <memory>
#include <string_view>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model : boost::noncopyable
{
//-----------------------------------------------------------------------------
public:
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath);
	static std::vector<std::unique_ptr<Model>> load(std::string_view _filePath);

//-----------------------------------------------------------------------------
	Model(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices);

	void bind() const;

	u64 getIndeciesCount() const noexcept;
	const boxf& getBoundingBox() const noexcept;

//-----------------------------------------------------------------------------
private:
	void calculateBoundingBox(const std::vector<Vertex>& _vertices) noexcept;

//-----------------------------------------------------------------------------
	VertexArray m_vertexArray;
	boxf m_boundingBox;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
