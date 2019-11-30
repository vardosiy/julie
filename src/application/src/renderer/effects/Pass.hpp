#pragma once

#include <vector>

class Fbo;
class Shader;
class Texture;
class Model;

class Pass
{
public:
	Pass() noexcept = default;

	void setTarget(Fbo * _target) noexcept;
	void setShader(Shader * _shader) noexcept;
	void setParameters(const std::vector<float> & _parameters) noexcept;
	void setTextures(const std::vector<Texture *> & _textures) noexcept;

	void run() const;

	static void initModel();
	static void destroyModel();

private:
	void initBlurOffsets();

private:
	Fbo * m_target;
	Shader * m_shader;

	std::vector<float> m_parameters;
	std::vector<int> m_texureUniformValue;
	std::vector<Texture *> m_textures;

	glm::vec2 m_blurOffsets;

	bool m_isDof;
	bool m_isBlur;

	static std::unique_ptr<Model> ms_model;
};
