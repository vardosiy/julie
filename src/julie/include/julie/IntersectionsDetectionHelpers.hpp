#pragma once

#include "julie/core/Types.hpp"
#include "julie/core/Aabb.hpp"

namespace jl {

bool intersects(const aabbf& _box, const rayf& _ray, float& _nearDistance, float& _farDistance);
bool intersects(const aabbf& _lhs, const aabbf& _rhs);

} // namespace jl
