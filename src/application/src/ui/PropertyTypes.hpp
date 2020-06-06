#pragma once

#include <QMetaType>

namespace jl {
class Model;
class Material;
}

struct ModelUiWrapper
{
	const jl::Model* model = nullptr;
};

struct MaterialUiWrapper
{
	const jl::Material* material = nullptr;
};

Q_DECLARE_METATYPE(ModelUiWrapper)
Q_DECLARE_METATYPE(MaterialUiWrapper)
