#include "renderer/Model.hpp"

#include "creation_helpers/ModelCreationHelper.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::loadFromFile(std::string_view _filePath)
{
	return ModelCreationHelper::loadFromFile(_filePath);
}

//-----------------------------------------------------------------------------

Model::Model(const std::vector<Vertex>& _vertices, const std::vector<u16>& _indices) noexcept
{
	m_meshes.emplace_back(_vertices, _indices);
	m_boundingBox = calculateBoundingBox(m_meshes);
}

//-----------------------------------------------------------------------------

Model::Model(std::vector<Mesh>&& _meshes) noexcept
	: m_meshes(std::move(_meshes))
{
	m_boundingBox = calculateBoundingBox(m_meshes);
}

//-----------------------------------------------------------------------------

u64 Model::getMeshedCount() const noexcept
{
	return m_meshes.size();
}

//-----------------------------------------------------------------------------

const Mesh& Model::getMesh(u64 _idx) const noexcept
{
	return m_meshes.at(_idx);
}

//-----------------------------------------------------------------------------

const boxf& Model::getBoundingBox() const noexcept
{
	return m_boundingBox;
}

//-----------------------------------------------------------------------------

boxf Model::calculateBoundingBox(const std::vector<Mesh>& _meshes) noexcept
{
	auto minFinder = [&_meshes](auto&& _valueGetter) -> float
	{
		float min = std::numeric_limits<float>::max();
		for (const Mesh& mesh : _meshes)
		{
			min = std::min(min, _valueGetter(mesh));
		}
		return min;
	};
	const float leftmost	= minFinder([](const Mesh& _mesh) { return _mesh.getBoundingBox().min.x; });
	const float lowest		= minFinder([](const Mesh& _mesh) { return _mesh.getBoundingBox().min.y; });
	const float farthest	= minFinder([](const Mesh& _mesh) { return _mesh.getBoundingBox().min.z; });

	auto maxFinder = [&_meshes](auto&& _valueGetter) -> float
	{
		float max = std::numeric_limits<float>::lowest();
		for (const Mesh& mesh : _meshes)
		{
			max = std::max(max, _valueGetter(mesh));
		}
		return max;
	};
	const float rightmost	= maxFinder([](const Mesh& _mesh) { return _mesh.getBoundingBox().max.x; });
	const float highest		= maxFinder([](const Mesh& _mesh) { return _mesh.getBoundingBox().max.y; });
	const float closest		= maxFinder([](const Mesh& _mesh) { return _mesh.getBoundingBox().max.z; });

	return boxf{
		glm::vec3{ leftmost, lowest, farthest },
		glm::vec3{ rightmost, highest, closest }
	};
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
