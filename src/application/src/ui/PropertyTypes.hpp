#pragma once

#include <QMetaType>

namespace jl {
class Model;
}

struct ModelUiWrapper
{
	const jl::Model* model;
};

Q_DECLARE_METATYPE(ModelUiWrapper)
