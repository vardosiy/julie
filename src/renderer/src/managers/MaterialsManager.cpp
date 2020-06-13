#include "renderer/managers/MaterialsManager.hpp"
#include "renderer/managers/ResourceManager.hpp"

#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

const std::string MaterialsManager::k_defaultMaterialName = "Default";

//-----------------------------------------------------------------------------

MaterialsManager::MaterialsManager()
{
	jl::Material& material = createMaterial(k_defaultMaterialName);
	material.setShader(getColorShader());
	material.setProperty("u_shininess",		128.0f);
	material.setProperty("u_opacity",		1.0f);
	material.setProperty("u_matAmbient",	glm::vec3(1.0f));
	material.setProperty("u_matDiffuse",	glm::vec3(1.0f));
	material.setProperty("u_matSpecular",	glm::vec3(0.0f));
	material.setProperty("u_texture2D",		static_cast<const jl::Texture*>(nullptr));
}

//-----------------------------------------------------------------------------

MaterialsManager::~MaterialsManager() = default;

//-----------------------------------------------------------------------------

void MaterialsManager::clear() noexcept
{
	m_materials.clear();
}

//-----------------------------------------------------------------------------

jl::Shader& MaterialsManager::getColorShader() const noexcept
{
	return *ResourceManager::getInstance().loadShader("res/shaders/MaterialColorShader.shdata");
}

//-----------------------------------------------------------------------------

jl::Shader& MaterialsManager::getTextureShader() const noexcept
{
	return *ResourceManager::getInstance().loadShader("res/shaders/MaterialTextureShader.shdata");
}

//-----------------------------------------------------------------------------

jl::Material& MaterialsManager::getDefaultMaterial() const noexcept
{
	ASSERT(findMaterial(k_defaultMaterialName));
	return *findMaterial(k_defaultMaterialName);
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
	ASSERTM(_name != k_defaultMaterialName, "Can not delete default material");
	if (_name != k_defaultMaterialName)
	{
		m_materials.erase(_name);
	}
}

//-----------------------------------------------------------------------------

void MaterialsManager::deleteMaterial(jl::Material& _material) noexcept
{
	const std::string& materialName = findMaterialName(_material);
	ASSERTM(materialName != k_defaultMaterialName, "Can not delete default material");

	if (!materialName.empty() && materialName != k_defaultMaterialName)
	{
		deleteMaterial(materialName);
	}
}

//-----------------------------------------------------------------------------

const std::string& MaterialsManager::findMaterialName(const jl::Material& _material) const noexcept
{
	for (const auto& [name, material] : m_materials)
	{
		if (material.get() == &_material)
		{
			return name;
		}
	}

	static const std::string k_unmanagedMaterialName = "";
	return k_unmanagedMaterialName;
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
