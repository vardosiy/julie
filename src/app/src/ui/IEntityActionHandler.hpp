#pragma once

#include "julie/ecs/Entity.hpp"

namespace jl {
class Material;
}

class IEntityActionHandler
{
public:
	virtual ~IEntityActionHandler() = default;

	virtual void entitySelected(jl::EntityRef _entity) = 0;
	virtual void materialSelected(jl::Material& _material) = 0;
	virtual void resetSelection() = 0;

	virtual void onEntityMoved(jl::EntityRef _entity) = 0;
	virtual void onEntityScaled(jl::EntityRef _entity) = 0;
};
