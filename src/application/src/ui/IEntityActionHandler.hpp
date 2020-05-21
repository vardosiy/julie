#pragma once

#include <QString>

namespace jl {
class Object;
}

class IEntityActionHandler
{
public:
	virtual ~IEntityActionHandler() = default;

	virtual void addObject() = 0;
	virtual void deleteObject(const QString& _name) = 0;
	virtual void objectSelected(const QString& _name) = 0;

	virtual void addMaterial() = 0;
	virtual void deleteMaterial(const QString& _name) = 0;
	virtual void materialSelected(const QString& _name) = 0;

	virtual void resetSelection() = 0;

	virtual void onObjectMoved(jl::Object& _object) = 0;
	virtual void onObjectScaled(jl::Object& _object) = 0;
};
