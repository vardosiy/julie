#pragma once

#include "save_restore/ISceneSaver.hpp"

#include <string_view>
#include <ostream>

class SceneSaver : public ISceneSaver
{
public:
	SceneSaver(std::ostream& _outputStream);

	void save(const jl::Scene& _scene) override;

private:
	std::ostream& m_outputStream;
};
