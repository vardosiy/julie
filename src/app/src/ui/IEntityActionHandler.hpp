#pragma once

namespace jl {
class Object;
class Material;
}

class IEntityActionHandler
{
public:
	virtual ~IEntityActionHandler() = default;

	virtual void objectSelected(jl::Object& _object) = 0;
	virtual void materialSelected(jl::Material& _material) = 0;
	virtual void resetSelection() = 0;

	virtual void onObjectMoved(jl::Object& _object) = 0;
	virtual void onObjectScaled(jl::Object& _object) = 0;
};
