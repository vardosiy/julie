#pragma once

#include <QMetaType>

#include <glm/vec3.hpp>

#include <functional>

namespace jl {
class Mesh;
class Model;
class Material;
}

struct ModelUiWrapper
{
	jl::Model* value = nullptr;
};

struct MaterialUiWrapper
{
	QString materialName;
	jl::Mesh* mesh = nullptr;
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
