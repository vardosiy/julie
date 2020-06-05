#pragma once

#include "renderer/Types.hpp"
#include "renderer/Mesh.hpp"

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

//-----------------------------------------------------------------------------
	Model(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices) noexcept;
	Model(std::vector<Mesh>&& _meshes) noexcept;

	u64 getMeshedCount() const noexcept;
	const Mesh& getMesh(u64 _idx) const noexcept;

	const boxf& getBoundingBox() const noexcept;

//-----------------------------------------------------------------------------
private:
	static boxf calculateBoundingBox(const std::vector<Mesh>& _meshes) noexcept;

//-----------------------------------------------------------------------------
	std::vector<Mesh> m_meshes;
	boxf m_boundingBox;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
