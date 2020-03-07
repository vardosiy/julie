#pragma once

#include "renderer/scene/lights/LightsData.hpp"

#include <boost/noncopyable.hpp>

#include <functional>
#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Shader;

class LightsHolder : boost::noncopyable
{
//-----------------------------------------------------------------------------
public:
	void update(float _dt);

	void bind(const Shader& _shader) const;

	const AmbientLightData& getAmbientLightData() const noexcept;
	void setAmbientLight(const AmbientLightData& _lightData) noexcept;

//-----------------------------------------------------------------------------
	void addPointLight(const PointLightData& _lightData) noexcept;
	void addDirectionalLight(const DirectionalLightData& _lightData) noexcept;

	//void forEachPointLight(const std::function<void(const PointLightData&)>& _callback);
	//void forEachDirectionalLight(const std::function<void(const DirectionalLightData&)>& _callback);

//-----------------------------------------------------------------------------
private:
	AmbientLightData m_ambientLight;

	//std::vector<PointLightData> m_pointLights;
	//std::vector<DirectionalLightData> m_directionalLights;

	std::vector<glm::vec4> m_pointLightsColors;
	std::vector<glm::vec3> m_pointLightsPositions;

	std::vector<glm::vec4> m_direcitonalLightsColors;
	std::vector<glm::vec3> m_direcitonalLightsDirection;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
