#include "julie/IntersectionsDetectionHelpers.hpp"

#include <utility>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

bool intersects(const aabbf& _box, const rayf& _ray, float& _nearDistance, float& _farDistance)
{
	float near = std::numeric_limits<float>::lowest();
	float far = std::numeric_limits<float>::max();

	for (int i = 0; i < 3; ++i)
	{
		if (_ray.end[i] == 0)
		{
			if ((_ray.start[i] < _box.min[i]) || (_ray.start[i] > _box.max[i]))
			{
				return false;
			}
		}
		else
		{
			float t1 = (_box.min[i] - _ray.start[i]) / _ray.end[i];
			float t2 = (_box.max[i] - _ray.start[i]) / _ray.end[i];

			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			if (t1 > near)
			{
				near = t1;
			}
			if (t2 < far)
			{
				far = t2;
			}
			if ((near > far) || (far < 0))
			{
				return false;
			}
		}
	}

	_nearDistance = near;
	_farDistance = far;
	return true;
};

//-----------------------------------------------------------------------------

bool intersects(const aabbf& _lhs, const aabbf& _rhs)
{
	return
		(_lhs.min.x < _rhs.max.x && _lhs.max.x > _rhs.min.x) &&
		(_lhs.min.y < _rhs.max.y && _lhs.max.y > _rhs.min.y) &&
		(_lhs.min.z < _rhs.max.z && _lhs.max.z > _rhs.min.z);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
