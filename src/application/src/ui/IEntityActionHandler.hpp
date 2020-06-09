#pragma once

namespace jl {
class Material;
}

class ObjectWrapper;

class IEntityActionHandler
{
public:
	virtual ~IEntityActionHandler() = default;

	virtual void objectSelected(ObjectWrapper& _objWrapper) = 0;
	virtual void materialSelected(jl::Material& _material) = 0;
	virtual void resetSelection() = 0;

	virtual void onObjectMoved(ObjectWrapper& _objWrapper) = 0;
	virtual void onObjectScaled(ObjectWrapper& _objWrapper) = 0;
};
