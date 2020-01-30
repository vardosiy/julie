#pragma once

namespace jl {
class Scene;
}

class ISceneSaver
{
public:
	virtual void save(const jl::Scene& _scene) = 0;
};
