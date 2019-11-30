#include "renderer/scene/objects/Object.hpp"

#include "renderer/scene/SceneManager.hpp"
#include "renderer/scene/camera/Camera.hpp"
#include "renderer/scene/lights/Light.hpp"
#include "renderer/scene/lights/AmbientLightData.hpp"
#include "renderer/scene/objects/Model.hpp"
#include "renderer/scene/FogData.hpp"

#include "renderer/shaders/Shader.hpp"

#include "renderer/gl_primitives/textures/Texture.hpp"
#include "renderer/gl_primitives/textures/CubeTexture.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/common/Axis.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

std::unique_ptr<Object> Object::create(Model & _model)
{
	auto object = std::make_unique<Object>();
	object->m_model = &_model;
	return object;
}

//-----------------------------------------------------------------------------

void Object::draw()
{
	m_shader->bind();
	m_model->bind();

	m_shader->bindAttributes();

	setUniforms();
	setTextures();

	m_shader->draw(m_model->getIndeciesCount());
}

//-----------------------------------------------------------------------------

void Object::update(float _deltaTime)
{
}

//-----------------------------------------------------------------------------

void Object::setShader(Shader & _shader) noexcept
{
	m_shader = &_shader;

	const Uniforms & uniforms = m_shader->getUniforms();

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

void Object::setTextures2D(std::vector<Texture *> && _textures) noexcept
{
	m_textures2D = std::move(_textures);
	m_bIsTexturesUpdated = true;
}

//-----------------------------------------------------------------------------

void Object::setCubeTextures(std::vector<CubeTexture *> && _textures) noexcept
{
	m_cubeTextures = std::move(_textures);
	m_bIsTexturesUpdated = true;
}

//-----------------------------------------------------------------------------

void Object::setPosition(const glm::vec3 & _vec) noexcept
{
	m_pos = _vec;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void Object::setRotation(const glm::vec3 & _vec) noexcept
{
	m_rotation = _vec;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void Object::setScale(const glm::vec3 & _vec) noexcept
{
	m_scale = _vec;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void Object::setParameters(const ObjectParameters & _params) noexcept
{
	m_params = _params;
}

//-----------------------------------------------------------------------------

void Object::setUniforms()
{
	const SceneManager & sceneMgr = SceneManager::getInstance();
	const Camera & cam = sceneMgr.getCamera();

	const Uniforms & uniforms = m_shader->getUniforms();

	if (uniforms.u_WVP != -1)
		m_shader->setUniformValue(uniforms.u_WVP, cam.getViewProjectionMatrix() * getWorldMatrix());

	if (uniforms.u_camPosition != -1)
		m_shader->setUniformValue(uniforms.u_camPosition, cam.getPosition());

	if (uniforms.u_W != -1)
		m_shader->setUniformValue(uniforms.u_W, getWorldMatrix());

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

	if (m_bIsLighted)
	{
		const AmbientLightData & ambientLightData = sceneMgr.getAmbientLightData();

		m_shader->setUniformValue(uniforms.u_ambientColor, ambientLightData.color);
		m_shader->setUniformValue(uniforms.u_ambientWeight, ambientLightData.weight);
		
		const std::vector<glm::vec4> & dirLightColors	= sceneMgr.getDirLightsColors();
		const std::vector<glm::vec4> & pointLightColors	= sceneMgr.getPointLightsColors();
		const std::vector<glm::vec3> & directions		= sceneMgr.getLightsDirections();
		const std::vector<glm::vec3> & positions		= sceneMgr.getLightsPositions();

		m_shader->setUniformValue(uniforms.u_dirLightColor,		dirLightColors.size(),		dirLightColors.data());
		m_shader->setUniformValue(uniforms.u_pointLightColor,	pointLightColors.size(),	pointLightColors.data());
		m_shader->setUniformValue(uniforms.u_lightDirection,	directions.size(),			directions.data());
		m_shader->setUniformValue(uniforms.u_lightPosition,		positions.size(),			positions.data());
	}

	if (m_bIsFogged)
	{
		const FogData & fog = sceneMgr.getFog();

		m_shader->setUniformValue(uniforms.u_fogStart, fog.start);
		m_shader->setUniformValue(uniforms.u_fogRange, fog.range);
		m_shader->setUniformValue(uniforms.u_fogColor, fog.color);
	}
}

//-----------------------------------------------------------------------------

void Object::setTextures()
{
	const Uniforms & uniforms = m_shader->getUniforms();

	if (m_bIsTexturesUpdated)
	{
		prepareTextureSlots();
	}

	int counter{ 0 };

	if (!m_textures2D.empty())
	{
		for (auto texture : m_textures2D)
		{
			texture->bind(counter++);
		}

		m_shader->setUniformValue(
			uniforms.u_texture2D,
			m_textures2D.size(),
			m_texture2DUniformValues.data()
		);
	}

	if (!m_cubeTextures.empty())
	{
		for (auto texture : m_cubeTextures)
		{
			texture->bind(counter++);
		}

		m_shader->setUniformValue(
			uniforms.u_cubeTexture,
			m_cubeTextures.size(),
			m_cubeTextureUniformValues.data()
		);
	}
}

//-----------------------------------------------------------------------------

void Object::prepareTextureSlots()
{
	const int textures2DCount{ static_cast<int>(m_textures2D.size()) };
	const int cubeTexturesCount{ static_cast<int>(m_cubeTextures.size()) };

	m_texture2DUniformValues.clear();
	m_texture2DUniformValues.reserve(m_textures2D.size());
	for (int i{ 0 }; i < textures2DCount; ++i)
	{
		m_texture2DUniformValues.push_back(i);
	}

	m_cubeTextureUniformValues.clear();
	m_cubeTextureUniformValues.reserve(m_cubeTextures.size());
	for (int i{ 0 }; i < cubeTexturesCount; ++i)
	{
		m_texture2DUniformValues.push_back(i + textures2DCount);
	}

	m_bIsTexturesUpdated = false;
}

//-----------------------------------------------------------------------------

glm::mat4 & Object::getWorldMatrix()
{
	if (m_bIsModified)
	{
		const glm::mat4 scale = glm::scale(m_scale);
		const glm::mat4 translate = glm::translate(m_pos);
		const glm::mat4 rotation =
			glm::rotate(m_rotation.x, constants::axis::x) *
			glm::rotate(m_rotation.y, constants::axis::y) *
			glm::rotate(m_rotation.z, constants::axis::z);

		m_worldMatrix = translate * rotation * scale;

		m_bIsModified = false;
	}

	return m_worldMatrix;
}

//-----------------------------------------------------------------------------
