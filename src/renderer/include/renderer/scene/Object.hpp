#pragma once

#include "renderer/common/Types.hpp"
#include "renderer/scene/ObjectParameters.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Model;
class Shader;
class Texture;
class CubeTexture;

class Object
{
public:
	Object(const Model & _model) noexcept;

	void draw(const Camera & _camera) const;
	void update(float _deltaTime);

	void setShader(const Shader & _shader) noexcept;
	void setTextures2D(std::vector<const Texture *> && _textures) noexcept;
	void setCubeTextures(std::vector<const CubeTexture *> && _textures) noexcept;

	void setPosition(const glm::vec3 & _vec) noexcept;
	void setRotation(const glm::vec3 & _vec) noexcept;
	void setScale(const glm::vec3 & _vec) noexcept;

	void translate(const glm::vec3 & _vec) noexcept;
	void rotate(const glm::vec3 & _vec) noexcept;

	void setParameters(const ObjectParameters & _params) noexcept;

private:
	void setUniforms(const Camera & _camera) const;
	void setTextures() const;

	void prepareTextureSlots();

	void recalculateWorldMatrix();

private:
	const Model * m_model;
	const Shader * m_shader;
	std::vector<const Texture *> m_textures2D;
	std::vector<const CubeTexture *> m_cubeTextures;

	std::vector<s32> m_texture2DUniformValues;
	std::vector<s32> m_cubeTextureUniformValues;

	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::mat4 m_worldMatrix;

	ObjectParameters m_params;

	bool m_bIsFogged;
	bool m_bIsLighted;

	bool m_bIsTransformChanged;
	bool m_bIsTexturesUpdated;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
