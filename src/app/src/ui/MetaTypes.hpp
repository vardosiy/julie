#pragma once

#include "julie/ecs/EntityId.hpp"

#include <QMetaType>
#include <glm/vec3.hpp>
#include <functional>

//-----------------------------------------------------------------------------

namespace jl {
class Material;
class Model;
class Texture;
class Shader;
}

//-----------------------------------------------------------------------------

struct EntityIdUiWrapper
{
	jl::EntityId value = jl::k_invalidEntityId;
};

struct MaterialUiWrapper
{
	jl::Material* value = nullptr;
};

//-----------------------------------------------------------------------------

struct ModelUiWrapper
{
	QString filePath;
	jl::Model* value = nullptr;
};

struct TextureUiWrapper
{
	QString filePath;
	jl::Texture* value = nullptr;
};

struct ShaderUiWrapper
{
	QString filePath;
	const jl::Shader* value = nullptr;
};

//-----------------------------------------------------------------------------

struct TransformVecUiWrapper
{
	glm::vec3 value{ 0.0f };
	std::function<void(const glm::vec3&)> editCallback;
};

struct ColorUiWrapper
{
	glm::vec3 value{ 0.0f };
	std::function<void(const glm::vec3&)> editCallback;
};

struct FloatValUiWrapper
{
	float value{ 0.0f };
	std::function<void(float)> editCallback;
};

//-----------------------------------------------------------------------------

Q_DECLARE_METATYPE(EntityIdUiWrapper)
Q_DECLARE_METATYPE(MaterialUiWrapper)

Q_DECLARE_METATYPE(ModelUiWrapper)
Q_DECLARE_METATYPE(TextureUiWrapper)
Q_DECLARE_METATYPE(ShaderUiWrapper)

Q_DECLARE_METATYPE(TransformVecUiWrapper)
Q_DECLARE_METATYPE(ColorUiWrapper)
Q_DECLARE_METATYPE(FloatValUiWrapper)

//-----------------------------------------------------------------------------
