#include "renderer/IntersectionsDetectionHelpers.hpp"

#include <utility>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

bool intersects(const boxf& _box, const rayf& _ray, float& _nearDistance, float& _farDistance)
{
	float t_near = std::numeric_limits<float>::lowest();
	float t_far = std::numeric_limits<float>::max();

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
			if (t1 > t_near)
			{
				t_near = t1;
			}
			if (t2 < t_far)
			{
				t_far = t2;
			}
			if ((t_near > t_far) || (t_far < 0))
			{
				return false;
			}
		}
	}

	_nearDistance = t_near;
	_farDistance = t_far;
	return true;
};

//-----------------------------------------------------------------------------

bool intersect(const boxf& _lhs, const boxf& _rhs)
{
	return
		(_lhs.min.x < _rhs.max.x && _lhs.max.x > _rhs.min.x) &&
		(_lhs.min.y < _rhs.max.y && _lhs.max.y > _rhs.min.y) &&
		(_lhs.min.z < _rhs.max.z && _lhs.max.z > _rhs.min.z);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
