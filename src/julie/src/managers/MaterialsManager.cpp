#include "julie/managers/MaterialsManager.hpp"
#include "julie/Material.hpp"

//-----------------------------------------------------------------------------

void MaterialsManager::clear() noexcept
{
	m_materials.clear();
}

//-----------------------------------------------------------------------------

size_t MaterialsManager::getMaterialsCount() const noexcept
{
	return m_materials.size();
}

//-----------------------------------------------------------------------------

jl::Material& MaterialsManager::createMaterial(const std::string& _name) noexcept
{
	jl::Material* result = findMaterial(_name);

	if (!result)
	{
		auto& material = m_materials.emplace_back(new jl::Material);
		material->setName(_name);

		result = material.get();
	}

	return *result;
}

//-----------------------------------------------------------------------------

jl::Material* MaterialsManager::findMaterial(const std::string& _name) const noexcept
{
	auto it = std::find_if(m_materials.begin(), m_materials.end(), [&_name](const auto& _material)
	{
		return _material->getName() == _name;
	});
	return it != m_materials.end() ? it->get() : nullptr;
}

//-----------------------------------------------------------------------------

void MaterialsManager::deleteMaterial(const std::string& _name) noexcept
{
	auto removeIt = std::remove_if(m_materials.begin(), m_materials.end(), [&_name](const auto& _material)
	{
		return _material->getName() == _name;
	});
	m_materials.erase(removeIt, m_materials.end());
}

//-----------------------------------------------------------------------------

void MaterialsManager::deleteMaterial(const jl::Material& _material) noexcept
{
	auto removeIt = std::remove_if(m_materials.begin(), m_materials.end(), [&_material](const auto& _mat)
	{
		return _mat.get() == &_material;
	});
	m_materials.erase(removeIt, m_materials.end());
}

//-----------------------------------------------------------------------------

void MaterialsManager::forEachMaterial(const std::function<void(jl::Material&)>& _callback)
{
	for (auto& material : m_materials)
	{
		_callback(*material);
	}
}

//-----------------------------------------------------------------------------

void MaterialsManager::forEachMaterial(const std::function<void(const jl::Material&)>& _callback) const
{
	for (auto& material : m_materials)
	{
		_callback(*material);
	}
}

//-----------------------------------------------------------------------------
