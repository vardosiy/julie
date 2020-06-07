#pragma once

#include "renderer/Types.hpp"

namespace jl {

bool intersects(const boxf& _box, const rayf& _ray, float& _nearDistance, float& _farDistance);
bool intersect(const boxf& _lhs, const boxf& _rhs);

} // namespace jl
