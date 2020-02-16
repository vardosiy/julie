#include "data/ShaderData.hpp"

#include "renderer/Shader.hpp"

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

ShaderData::ShaderData(std::string _name)
	: DataEntity(std::move(_name))
{
}

//-----------------------------------------------------------------------------

ShaderData::~ShaderData() = default;

//-----------------------------------------------------------------------------

const std::string& ShaderData::getVsFile() const noexcept
{
	return m_vsFile;
}

//-----------------------------------------------------------------------------

const std::string& ShaderData::getFsFile() const noexcept
{
	return m_fsFile;
}

//-----------------------------------------------------------------------------

const jl::Shader* ShaderData::getShader() const noexcept
{
	return m_shader.get();
}

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------