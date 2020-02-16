#pragma once

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ICamera;

class IRenderable
{
public:
	virtual ~IRenderable() = default;

	virtual void update(float _dt) = 0;
	virtual void render(const ICamera& _camera) const noexcept = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
