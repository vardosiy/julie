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

class Model;
class Shader;
class Texture;
class CubeTexture;

class Object
{
public:
	static std::unique_ptr<Object> create(const Model & _model);

public:
	void draw();

	void update(float _deltaTime);

	void setShader(const Shader & _shader) noexcept;
	void setTextures2D(std::vector<Texture *> && _textures) noexcept;
	void setCubeTextures(std::vector<CubeTexture *> && _textures) noexcept;

	void setPosition(const glm::vec3 & _vec) noexcept;
	void setRotation(const glm::vec3 & _vec) noexcept;
	void setScale(const glm::vec3 & _vec) noexcept;

	void translate(const glm::vec3 & _vec) noexcept; // TODO
	void rotate(const glm::vec3 & _vec) noexcept; // TODO

	void setParameters(const ObjectParameters & _params) noexcept;

private:
	void setUniforms();
	void setTextures();

	void prepareTextureSlots();

	void recalculateWorldMatrix();

private:
	const Model * m_model;
	const Shader * m_shader;
	std::vector<Texture *> m_textures2D;
	std::vector<CubeTexture *> m_cubeTextures;

	std::vector<s32> m_texture2DUniformValues;
	std::vector<s32> m_cubeTextureUniformValues;

	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::mat4 m_worldMatrix;

	ObjectParameters m_params;

	bool m_bIsFogged;
	bool m_bIsLighted;

	bool m_bIsModified;
	bool m_bIsTexturesUpdated;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
