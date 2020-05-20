#include "renderer/Renderer.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"

#include "renderer/primitives/VertexArray.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Renderer::s_shader;
std::unique_ptr<VertexArray> Renderer::s_vertexArray;

const std::string Renderer::k_primitivesShaderVsSource = R"(
	#version 330 core

	layout (location = 0) in vec3 a_posL;
	uniform mat4 u_WVP;

	void main()
	{
		gl_Position = u_WVP * vec4(a_posL, 1.0);
	}
)";

const std::string Renderer::k_primitivesShaderFsSource = R"(
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
	ASSERT(gladLoadGL());

	LOG_INFO(
		"OpenGL info\n-> Vendor: {}\n-> Renderer: {}\n-> Version: {}",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION)
	);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	s_shader = Shader::create(k_primitivesShaderVsSource, k_primitivesShaderFsSource);

	s_vertexArray.reset(new VertexArray);
	s_vertexArray->setVertexBuffer(std::make_unique<VertexBuffer>(1024));
	s_vertexArray->setIndexBuffer(std::make_unique<IndexBuffer>(1024));

	ASSERT(s_shader);
	ASSERT(s_vertexArray);
}

//-----------------------------------------------------------------------------

void Renderer::shutdown()
{
	s_shader.reset();
	s_vertexArray.reset();
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
	vertBuf[0].pos = glm::vec3(_box.min.x, _box.max.y, _box.min.z);
	vertBuf[1].pos = glm::vec3(_box.max.x, _box.max.y, _box.min.z);
	vertBuf[2].pos = _box.min;
	vertBuf[3].pos = glm::vec3(_box.max.x, _box.min.y, _box.min.z);

	vertBuf[4].pos = glm::vec3(_box.min.x, _box.max.y, _box.max.z);
	vertBuf[5].pos = _box.max;
	vertBuf[6].pos = glm::vec3(_box.min.x, _box.min.y, _box.max.z);
	vertBuf[7].pos = glm::vec3(_box.max.x, _box.min.y, _box.max.z);

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

void Renderer::clear() noexcept
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-----------------------------------------------------------------------------

void Renderer::setClearColor(const glm::vec4& _color) noexcept
{
	glClearColor(_color.r, _color.g, _color.b, _color.a);
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
