#pragma once

#include "data/DataEntity.hpp"

namespace jl {
class Shader;
}

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class ShaderEntity : DataEntity
{
public:
	ShaderEntity(Id _id);
	~ShaderEntity();

	std::string_view getVsFile() const noexcept;
	std::string_view getFsFile() const noexcept;

	const jl::Shader* getShader() const noexcept;

private:
	std::string m_fsFile;
	std::string m_vsFile;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
