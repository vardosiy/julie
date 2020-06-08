#pragma once

#include <QMetaType>

#include <glm/vec3.hpp>

#include <functional>

namespace jl {
class Model;
class Material;
}

struct ModelUiWrapper
{
	const jl::Model* value = nullptr;
};

struct MaterialUiWrapper
{
	const jl::Material* value = nullptr;
};

struct TransformVecUiWrapper
{
	glm::vec3 value{ 0.0f };
	std::function<void(const glm::vec3&)> setter;
};

struct ColorUiWrapper
{
	glm::vec3 value{ 0.0f };
};

Q_DECLARE_METATYPE(ModelUiWrapper)
Q_DECLARE_METATYPE(MaterialUiWrapper)
Q_DECLARE_METATYPE(TransformVecUiWrapper)
Q_DECLARE_METATYPE(ColorUiWrapper)
