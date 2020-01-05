#include "renderer/scene/Object.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"
#include "renderer/scene/Light.hpp"
#include "renderer/scene/AmbientLightData.hpp"
#include "renderer/scene/Model.hpp"
#include "renderer/scene/FogData.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/common/Axis.hpp"
#include "renderer/shaders/Shader.hpp"

#include "renderer/gl_primitives/Texture.hpp"
#include "renderer/gl_primitives/CubeTexture.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Object::Object(const Model & _model) noexcept
	: m_model(&_model)
	, m_shader(nullptr)
	, m_pos(0.0f, 0.0f, 0.0f)
	, m_scale(0.0f, 0.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_worldMatrix(1.0f)
	, m_bIsFogged(false)
	, m_bIsLighted(false)
	, m_bIsTransformChanged(false)
	, m_bIsTexturesUpdated(false)
{
	memset(&m_params, 0, sizeof(m_params));
}

//-----------------------------------------------------------------------------

void Object::draw(const Camera & _camera) const
{
	if (m_shader)
	{
		m_shader->bind();
		setUniforms(_camera);
		m_shader->draw(*m_model);
	}
}

//-----------------------------------------------------------------------------

void Object::update(float _deltaTime)
{
	if (m_bIsTransformChanged)
	{
		recalculateWorldMatrix();
		m_bIsTransformChanged = false;
	}

	if (m_bIsTexturesUpdated)
	{
		prepareTextureSlots();
		m_bIsTexturesUpdated = false;
	}
}

//-----------------------------------------------------------------------------

void Object::setShader(const Shader & _shader) noexcept
{
	m_shader = &_shader;

	const ShaderUniforms & uniforms = m_shader->getUniforms();

	m_bIsFogged =
		uniforms.u_fogStart != -1 &&
		uniforms.u_fogRange != -1 &&
		uniforms.u_fogColor != -1;

	m_bIsLighted =
		uniforms.u_ambientWeight != -1 &&
		uniforms.u_ambientColor != -1 &&
		uniforms.u_dirLightColor != -1 &&
		uniforms.u_pointLightColor != -1 &&
		uniforms.u_lightDirection != -1 &&
		uniforms.u_lightPosition != -1;
}

//-----------------------------------------------------------------------------

void Object::setTextures2D(std::vector<const Texture *> && _textures) noexcept
{
	m_textures2D = std::move(_textures);
	m_bIsTexturesUpdated = true;
}

//-----------------------------------------------------------------------------

void Object::setCubeTextures(std::vector<const CubeTexture *> && _textures) noexcept
{
	m_cubeTextures = std::move(_textures);
	m_bIsTexturesUpdated = true;
}

//-----------------------------------------------------------------------------

void Object::setPosition(const glm::vec3 & _vec) noexcept
{
	m_pos = _vec;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setRotation(const glm::vec3 & _vec) noexcept
{
	m_rotation = _vec;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setScale(const glm::vec3 & _vec) noexcept
{
	m_scale = _vec;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::translate(const glm::vec3 & _vec) noexcept
{
	m_pos += _vec;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::rotate(const glm::vec3 & _vec) noexcept
{
	m_rotation += _vec;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setParameters(const ObjectParameters & _params) noexcept
{
	m_params = _params;
}

//-----------------------------------------------------------------------------

void Object::setUniforms(const Camera & _camera) const
{
	const ShaderUniforms & uniforms = m_shader->getUniforms();

	if (uniforms.u_WVP != -1)
		m_shader->setUniformValue(uniforms.u_WVP, _camera.getViewProjectionMatrix() * m_worldMatrix);

	if (uniforms.u_camPosition != -1)
		m_shader->setUniformValue(uniforms.u_camPosition, _camera.getPosition());

	if (uniforms.u_W != -1)
		m_shader->setUniformValue(uniforms.u_W, m_worldMatrix);

	if (uniforms.u_tilingFactor != -1)
		m_shader->setUniformValue(uniforms.u_tilingFactor, m_params.tilingFactor);

	if (uniforms.u_dMax != -1)
		m_shader->setUniformValue(uniforms.u_dMax, m_params.dMax);

	if (uniforms.u_depthAdjust != -1)
		m_shader->setUniformValue(uniforms.u_depthAdjust, m_params.depthAdjust);

	if (uniforms.u_depthDispl != -1)
		m_shader->setUniformValue(uniforms.u_depthDispl, m_params.depthDispl);

	if (uniforms.u_specularPower != -1)
		m_shader->setUniformValue(uniforms.u_specularPower, m_params.specularPower);

	if (uniforms.u_color != -1)
		m_shader->setUniformValue(uniforms.u_color, m_params.color);

	if (uniforms.u_time != -1)
		m_shader->setUniformValue(uniforms.u_time, Globals::s_timeTotal);

	//if (m_bIsLighted)
	//{
	//	const AmbientLightData & ambientLightData = sceneMgr.getAmbientLightData();
	//
	//	m_shader->setUniformValue(uniforms.u_ambientColor, ambientLightData.color);
	//	m_shader->setUniformValue(uniforms.u_ambientWeight, ambientLightData.weight);
	//	
	//	const std::vector<glm::vec4> & dirLightColors	= sceneMgr.getDirLightsColors();
	//	const std::vector<glm::vec4> & pointLightColors	= sceneMgr.getPointLightsColors();
	//	const std::vector<glm::vec3> & directions		= sceneMgr.getLightsDirections();
	//	const std::vector<glm::vec3> & positions		= sceneMgr.getLightsPositions();
	//
	//	m_shader->setUniformValue(uniforms.u_dirLightColor,		dirLightColors.size(),		dirLightColors.data());
	//	m_shader->setUniformValue(uniforms.u_pointLightColor,	pointLightColors.size(),	pointLightColors.data());
	//	m_shader->setUniformValue(uniforms.u_lightDirection,	directions.size(),			directions.data());
	//	m_shader->setUniformValue(uniforms.u_lightPosition,		positions.size(),			positions.data());
	//}

	//if (m_bIsFogged)
	//{
	//	const FogData & fog = sceneMgr.getFog();
	//
	//	m_shader->setUniformValue(uniforms.u_fogStart, fog.start);
	//	m_shader->setUniformValue(uniforms.u_fogRange, fog.range);
	//	m_shader->setUniformValue(uniforms.u_fogColor, fog.color);
	//}

	setTextures();
}

//-----------------------------------------------------------------------------

void Object::setTextures() const
{
	const ShaderUniforms & uniforms = m_shader->getUniforms();

	u16 counter = 0;

	if (!m_textures2D.empty())
	{
		for (auto texture : m_textures2D)
		{
			texture->bind(counter++);
		}
		m_shader->setUniformValue(uniforms.u_texture2D, m_texture2DUniformValues);
	}

	if (!m_cubeTextures.empty())
	{
		for (auto texture : m_cubeTextures)
		{
			texture->bind(counter++);
		}
		m_shader->setUniformValue(uniforms.u_cubeTexture, m_cubeTextureUniformValues);
	}
}

//-----------------------------------------------------------------------------

void Object::prepareTextureSlots()
{
	const s32 textures2DCount = static_cast<s32>(m_textures2D.size());
	const s32 cubeTexturesCount = static_cast<s32>(m_cubeTextures.size());

	m_texture2DUniformValues.clear();
	m_texture2DUniformValues.reserve(m_textures2D.size());
	for (s32 i = 0; i < textures2DCount; ++i)
	{
		m_texture2DUniformValues.push_back(i);
	}

	m_cubeTextureUniformValues.clear();
	m_cubeTextureUniformValues.reserve(m_cubeTextures.size());
	for (s32 i = 0; i < cubeTexturesCount; ++i)
	{
		m_texture2DUniformValues.push_back(i + textures2DCount);
	}
}

//-----------------------------------------------------------------------------

void Object::recalculateWorldMatrix()
{
	const glm::mat4 scale = glm::scale(m_scale);
	const glm::mat4 translate = glm::translate(m_pos);
	const glm::mat4 rotation =
		glm::rotate(m_rotation.x, constants::axis::x) *
		glm::rotate(m_rotation.y, constants::axis::y) *
		glm::rotate(m_rotation.z, constants::axis::z);

	m_worldMatrix = translate * (rotation * scale);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
