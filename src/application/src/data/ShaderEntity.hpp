#pragma once

#include "data/DataEntity.hpp"

namespace jl {
class Shader;
}

class ShaderEntity : DataEntity
{
public:
	ShaderEntity(Id _id);
	~ShaderEntity();

	const Id& getId() const noexcept;

private:
	Id m_id;
};
