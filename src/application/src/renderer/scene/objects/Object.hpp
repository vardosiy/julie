#pragma once

#include "renderer/scene/objects/ObjectParameters.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

class Model;
class Shader;
class Texture;
class CubeTexture;

class Object
{
public:
	static std::unique_ptr<Object> create(Model & _model);

public:
	void draw();

	void update(float _deltaTime);

	void setShader(Shader & _shader) noexcept;
	void setTextures2D(std::vector<Texture *> && _textures) noexcept;
	void setCubeTextures(std::vector<CubeTexture *> && _textures) noexcept;

	void setPosition(const glm::vec3 & _vec) noexcept;
	void setRotation(const glm::vec3 & _vec) noexcept;
	void setScale(const glm::vec3 & _vec) noexcept;

	void setParameters(const ObjectParameters & _params) noexcept;

private:
	void setUniforms();
	void setTextures();

	void prepareTextureSlots();

	glm::mat4 & getWorldMatrix();

private:
	Model * m_model;
	Shader * m_shader;
	std::vector<Texture *> m_textures2D;
	std::vector<CubeTexture *> m_cubeTextures;

	std::vector<GLint> m_texture2DUniformValues;
	std::vector<GLint> m_cubeTextureUniformValues;

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
