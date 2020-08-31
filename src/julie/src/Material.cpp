#include "julie/Material.hpp"
#include "julie/Shader.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

const std::vector<Material::Property>& Material::getProperties() const noexcept
{
	return m_properties;
}

//-----------------------------------------------------------------------------

void jl::Material::clearProperties() noexcept
{
	m_properties.clear();
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
