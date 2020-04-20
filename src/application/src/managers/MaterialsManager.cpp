#include "managers/MaterialsManager.hpp"
#include "renderer/Material.hpp"

//-----------------------------------------------------------------------------

void MaterialsManager::clear() noexcept
{
	m_materials.clear();
}

//-----------------------------------------------------------------------------

bool MaterialsManager::hasMaterial(const std::string& _name) const noexcept
{
	return m_materials.find(_name) != m_materials.end();
}

//-----------------------------------------------------------------------------

jl::Material& MaterialsManager::getMaterial(const std::string& _name) noexcept
{
	return m_materials[_name];
}

//-----------------------------------------------------------------------------

const std::string& MaterialsManager::getMaterialName(const jl::Material& _material) const noexcept
{
	for (const auto& [name, material] : m_materials)
	{
		if (&material == &_material)
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
		_callback(name, material);
	}
}

//-----------------------------------------------------------------------------
