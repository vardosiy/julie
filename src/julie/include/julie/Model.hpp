#pragma once

#include "julie/core/Types.hpp"
#include "julie/core/Aabb.hpp"
#include "julie/Mesh.hpp"

#include "utils/Noncopyable.hpp"

#include <vector>
#include <memory>
#include <string_view>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model : utils::Noncopyable
{
//-----------------------------------------------------------------------------
public:
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath, bool _loadMaterials);

//-----------------------------------------------------------------------------
	Model(const std::vector<Vertex>& _vertices, const std::vector<index_t>& _indices) noexcept;
	Model(std::vector<Mesh>&& _meshes) noexcept;

	Model(Model&&) = default;
	Model& operator=(Model&&) = default;

	size_t getMeshesCount() const noexcept;

	Mesh& getMesh(size_t _idx) noexcept;
	const Mesh& getMesh(size_t _idx) const noexcept;

	const aabbf& getBoundingBox() const noexcept;

//-----------------------------------------------------------------------------
private:
	static aabbf calculateBoundingBox(const std::vector<Mesh>& _meshes) noexcept;

//-----------------------------------------------------------------------------
	std::vector<Mesh> m_meshes;
	aabbf m_boundingBox;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
