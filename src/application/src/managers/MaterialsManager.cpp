#include "managers/MaterialsManager.hpp"
#include "renderer/Material.hpp"

//-----------------------------------------------------------------------------

void MaterialsManager::clear() noexcept
{
	m_materials.clear();
}

//-----------------------------------------------------------------------------

jl::Material& MaterialsManager::createMaterial(const std::string& _name) noexcept
{
	std::unique_ptr<jl::Material>& material = m_materials[_name];

	if (!material)
	{
		material.reset(new jl::Material);
	}

	return *material;
}

//-----------------------------------------------------------------------------

jl::Material* MaterialsManager::getMaterial(const std::string& _name) const noexcept
{
	auto it = m_materials.find(_name);
	return it != m_materials.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

bool MaterialsManager::hasMaterial(const std::string& _name) const noexcept
{
	return m_materials.find(_name) != m_materials.end();
}

//-----------------------------------------------------------------------------

const std::string& MaterialsManager::getMaterialName(const jl::Material& _material) const noexcept
{
	for (const auto& [name, material] : m_materials)
	{
		if (material.get() == &_material)
		{
			return name;
		}
	}
	return "";
}

//-----------------------------------------------------------------------------

void MaterialsManager::forEachMaterial(const std::function<void(const std::string&, jl::Material&)>& _callback)
{
	for (auto& [name, material] : m_materials)
	{
		_callback(name, *material);
	}
}

//-----------------------------------------------------------------------------
