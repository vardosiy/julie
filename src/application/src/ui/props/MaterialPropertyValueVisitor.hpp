#include "ui/props/PropertyTypes.hpp"
#include "utils/Utils.hpp"

#include <QVariant>

class MaterialPropertyValueVisitor
{
public:
	QVariant operator() (const glm::vec3& _value) const noexcept
	{
		return QVariant::fromValue(ColorUiWrapper{ _value });
	}

	QVariant operator() (float _value) const noexcept
	{
		return QVariant(_value);
	}

	template<typename T>
	QVariant operator() (const T& _value) const noexcept
	{
		//ASSERT(0);
		return QVariant();
	}
};
