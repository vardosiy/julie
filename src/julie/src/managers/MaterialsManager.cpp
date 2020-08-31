#include "julie/managers/MaterialsManager.hpp"
#include "julie/managers/ResourceManager.hpp"

#include "julie/Material.hpp"
#include "julie/Shader.hpp"

#include "utils/Utils.hpp"

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

jl::Material* MaterialsManager::findMaterial(const std::string& _name) const noexcept
{
	auto it = m_materials.find(_name);
	return it != m_materials.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

void MaterialsManager::deleteMaterial(const std::string& _name) noexcept
{
	m_materials.erase(_name);
}

//-----------------------------------------------------------------------------

void MaterialsManager::deleteMaterial(jl::Material& _material) noexcept
{
	const std::string materialName = findMaterialName(_material);
	if (!materialName.empty())
	{
		deleteMaterial(materialName);
	}
}

//-----------------------------------------------------------------------------

std::string MaterialsManager::findMaterialName(const jl::Material& _material) const noexcept
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

void MaterialsManager::forEachMaterial(const std::function<void(const std::string&, const jl::Material&)>& _callback) const
{
	for (auto& [name, material] : m_materials)
	{
		_callback(name, *material);
	}
}

//-----------------------------------------------------------------------------
