#pragma once

#include <QMetaType>
#include <glm/vec3.hpp>
#include <functional>

namespace jl {
class Mesh;
class Model;
class Material;
class Texture;
}

//-----------------------------------------------------------------------------

struct ModelUiWrapper
{
	jl::Model* value = nullptr;
};

struct TextureUiWrapper
{
	const jl::Texture* value = nullptr;
};

struct MaterialUiWrapper
{
	QString materialName;
	jl::Mesh* mesh = nullptr;
};

struct FloatValUiWrapper
{
	float value{ 0.0f };
	std::function<void(float)> editCallback;
};

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

//-----------------------------------------------------------------------------

Q_DECLARE_METATYPE(ModelUiWrapper)
Q_DECLARE_METATYPE(TextureUiWrapper)
Q_DECLARE_METATYPE(MaterialUiWrapper)
Q_DECLARE_METATYPE(FloatValUiWrapper)
Q_DECLARE_METATYPE(TransformVecUiWrapper)
Q_DECLARE_METATYPE(ColorUiWrapper)

//-----------------------------------------------------------------------------
