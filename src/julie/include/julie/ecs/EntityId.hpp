#pragma once

#include "utils/Identifier.hpp"

namespace jl {

using EntityId = utils::Identifier<class EntityIdClass, int>;

constexpr EntityId k_invalidEntityId{ 0 };

} // namespace jl
