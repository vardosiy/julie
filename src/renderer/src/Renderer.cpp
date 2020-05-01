#include "renderer/Renderer.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"

#include "renderer/primitives/VertexArray.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Renderer::s_shader;
std::unique_ptr<VertexArray> Renderer::s_vertexArray;

const std::string Renderer::k_boxShaderVsSource = R"(
	#version 330 core

	layout (location = 0) in vec3 a_posL;
	uniform mat4 u_WVP;

	void main()
	{
		gl_Position = u_WVP * vec4(a_posL, 1.0);
	}
)";
const std::string Renderer::k_boxShaderFsSource = R"(
	#version 330 core
	precision mediump float;

	out vec4 o_color;
	uniform vec4 u_color;

	void main()
	{
		o_color = u_color;
	}
)";

//-----------------------------------------------------------------------------

void Renderer::init()
{
	constexpr u64 k_vertexBufferSize = 1024;
	constexpr u64 k_indexBufferSize = 1024;

	s_vertexArray.reset(new VertexArray);
	s_vertexArray->setVertexBuffer(std::make_unique<VertexBuffer>(k_vertexBufferSize));
	s_vertexArray->setIndexBuffer(std::make_unique<IndexBuffer>(k_indexBufferSize));

	s_shader = Shader::create(k_boxShaderVsSource, k_boxShaderFsSource);
	ASSERT(s_shader);
}

//-----------------------------------------------------------------------------

void Renderer::shutdown()
{
	s_vertexArray.reset();
	s_shader.reset();
}

//-----------------------------------------------------------------------------

void Renderer::draw(const Model& _model) noexcept
{
	_model.bind();
	glDrawElements(GL_TRIANGLES, _model.getIndeciesCount(), GL_UNSIGNED_SHORT, nullptr);
}

//-----------------------------------------------------------------------------

void Renderer::draw(const boxf& _box, const glm::vec4& _color, const glm::mat4& _transform) noexcept
{
	s_shader->bind();
	s_shader->setUniform("u_color", _color);
	s_shader->setUniform("u_WVP", _transform);

	s_vertexArray->bind();
	VertexBuffer* vertexBuffer = s_vertexArray->getVertexBuffer();
	IndexBuffer* indexBuffer = s_vertexArray->getIndexBuffer();

	Vertex vertBuf[8];
	vertBuf[0].pos = _box.pos1;
	vertBuf[1].pos = glm::vec3(_box.pos2.x, _box.pos1.y, _box.pos1.z);
	vertBuf[2].pos = glm::vec3(_box.pos1.x, _box.pos2.y, _box.pos1.z);
	vertBuf[3].pos = glm::vec3(_box.pos2.x, _box.pos2.y, _box.pos1.z);

	vertBuf[4].pos = glm::vec3(_box.pos1.x, _box.pos1.y, _box.pos2.z);
	vertBuf[5].pos = glm::vec3(_box.pos2.x, _box.pos1.y, _box.pos2.z);
	vertBuf[6].pos = glm::vec3(_box.pos1.x, _box.pos2.y, _box.pos2.z);
	vertBuf[7].pos = _box.pos2;

	vertexBuffer->bufferData(vertBuf, std::size(vertBuf), 0);

	u16 indexBuf[] = {
		0, 4, 1, 5, 2, 6, 3, 7,
		0, 1, 4, 5, 2, 3, 6, 7,
		0, 2, 1, 3, 4, 6, 5, 7
	};

	indexBuffer->bufferData(indexBuf, std::size(indexBuf));

	glDrawElements(GL_LINES, indexBuffer->getCount(), GL_UNSIGNED_SHORT, nullptr);
}

//-----------------------------------------------------------------------------

void Renderer::setFrontPolygonsMode(PolygonMode _mode) noexcept
{
	glPolygonMode(GL_FRONT, polygonModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void Renderer::setBackPolygonsMode(PolygonMode _mode) noexcept
{
	glPolygonMode(GL_BACK, polygonModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void Renderer::setClearColor(const glm::vec4& _color) noexcept
{
	glClearColor(_color.r, _color.g, _color.b, _color.a);
}

//-----------------------------------------------------------------------------

s32 Renderer::polygonModeToGlValue(PolygonMode _mode) noexcept
{
	switch (_mode)
	{
		case PolygonMode::Fill: return GL_FILL;
		case PolygonMode::Line: return GL_LINE;
	}

	ASSERT(0);
	return GL_FILL;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
