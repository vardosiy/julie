#include "julie/Model.hpp"

#include "creation_helpers/ModelCreationHelper.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Model::loadFromFile(std::string_view _filePath, bool _loadMaterials)
{
	return ModelCreationHelper::loadFromFile(_filePath, _loadMaterials);
}

//-----------------------------------------------------------------------------

Model::Model(const std::vector<Vertex>& _vertices, const std::vector<index_t>& _indices) noexcept
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

size_t Model::getMeshesCount() const noexcept
{
	return m_meshes.size();
}

//-----------------------------------------------------------------------------

Mesh& Model::getMesh(size_t _idx) noexcept
{
	return m_meshes[_idx];
}

//-----------------------------------------------------------------------------

const Mesh& Model::getMesh(size_t _idx) const noexcept
{
	return m_meshes[_idx];
}

//-----------------------------------------------------------------------------

const aabbf& Model::getBoundingBox() const noexcept
{
	return m_boundingBox;
}

//-----------------------------------------------------------------------------

aabbf Model::calculateBoundingBox(const std::vector<Mesh>& _meshes) noexcept
{
	auto minFinder = [&_meshes](int _dimensionIdx) -> float
	{
		float min = std::numeric_limits<float>::max();
		for (const Mesh& mesh : _meshes)
		{
			const float meshValue = mesh.getBoundingBox().min[_dimensionIdx];
			min = std::min(min, meshValue);
		}
		return min;
	};
	const float leftmost	= minFinder(0);
	const float lowest		= minFinder(1);
	const float farthest	= minFinder(2);

	auto maxFinder = [&_meshes](int _dimensionIdx) -> float
	{
		float max = std::numeric_limits<float>::lowest();
		for (const Mesh& mesh : _meshes)
		{
			const float meshValue = mesh.getBoundingBox().max[_dimensionIdx];
			max = std::max(max, meshValue);
		}
		return max;
	};
	const float rightmost	= maxFinder(0);
	const float highest		= maxFinder(1);
	const float closest		= maxFinder(2);

	return aabbf{
		glm::vec3{ leftmost, lowest, farthest },
		glm::vec3{ rightmost, highest, closest }
	};
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
