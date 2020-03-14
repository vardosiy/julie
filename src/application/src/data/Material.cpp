#include "data/Material.hpp"

#include "managers/ResourceManager.hpp"

#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/CubeTexture.hpp"

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

Material::Material(std::string _name)
	: DataEntity(std::move(_name))
{
}

//-----------------------------------------------------------------------------

Material::~Material() = default;

//-----------------------------------------------------------------------------

const jl::Material& Material::getMaterial() const noexcept
{
	return m_material;
}

//-----------------------------------------------------------------------------

void Material::setShader(std::string _val)
{
	m_shader = _val;

	const jl::Shader* shader = ResourceManager::getInstance().loadShader(_val);
	if (shader)
	{
		m_material.setShader(*shader);
	}
}

//-----------------------------------------------------------------------------

void Material::setTexture(std::string _propertyName, std::string _val)
{

}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
