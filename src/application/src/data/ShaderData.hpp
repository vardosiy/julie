#pragma once

#include "data/DataEntity.hpp"

#include <memory>

namespace jl {
class Shader;
}

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class ShaderData : public DataEntity
{
public:
	ShaderData(std::string _name);
	~ShaderData();

	const std::string& getVsFile() const noexcept;
	const std::string& getFsFile() const noexcept;

	const jl::Shader* getShader() const noexcept;

private:
	std::string m_vsFile;
	std::string m_fsFile;

	std::unique_ptr<jl::Shader> m_shader;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
