#pragma once

#include "renderer/effects/Pass.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Effect
{
public:
	Effect() noexcept = default;

	void addPass(const Pass & _pass);
	void apply() const;

private:
	std::vector<Pass> m_passes;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
