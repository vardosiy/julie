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
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath, bool _loadMaterials);

//-----------------------------------------------------------------------------
	Model(const std::vector<Vertex>& _vertices, const std::vector<index_t>& _indices) noexcept;
	Model(std::vector<Mesh>&& _meshes) noexcept;

	u32 getMeshesCount() const noexcept;

	Mesh& getMesh(u32 _idx) noexcept;
	const Mesh& getMesh(u32 _idx) const noexcept;

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
