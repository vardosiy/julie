#include <glad/glad.h>

#include "ui/AppGlWidget.hpp"
#include "managers/ResourceManager.hpp"

#include "renderer/Renderer.hpp"
#include "renderer/Globals.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"

#include "renderer/primitives/Fbo.hpp"
#include "renderer/Shader.hpp"

#include "utils/LogDefs.hpp"

#include <QKeyEvent>

//-----------------------------------------------------------------------------

AppGlWidget::AppGlWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, m_updateTimer(this)
{
}

//-----------------------------------------------------------------------------

void AppGlWidget::setDrawMode(DrawMode _drawMode)
{
	jl::PolygonMode frontPolygonsMode;
	jl::PolygonMode backPolygonsMode;

	switch (_drawMode)
	{
		case DrawMode::Fill:
		{
			frontPolygonsMode = jl::PolygonMode::Fill;
			backPolygonsMode = jl::PolygonMode::Fill;
		}
		break;

		case DrawMode::Edges:
		{
			frontPolygonsMode = jl::PolygonMode::Line;
			backPolygonsMode = jl::PolygonMode::Line;
		}
		break;

		default:
		{
			assert(0);
		}
	}

	m_prerenderCommand = [frontPolygonsMode, backPolygonsMode]()
	{
		jl::Renderer::setFrontPolygonsMode(frontPolygonsMode);
		jl::Renderer::setBackPolygonsMode(backPolygonsMode);
	};
	m_postrenderCommand = []()
	{
		jl::Renderer::setFrontPolygonsMode(jl::PolygonMode::Fill);
		jl::Renderer::setBackPolygonsMode(jl::PolygonMode::Fill);
	};
}

//-----------------------------------------------------------------------------

void AppGlWidget::initializeGL()
{
	gladLoadGL();

	LOG_INFO(
		"OpenGL info\n-> Vendor: {}\n-> Renderer: {}\n-> Version: {}",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION)
	);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_sandbox.init();

	connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_updateTimer.start(1);
}

//-----------------------------------------------------------------------------

void AppGlWidget::resizeGL(int _w, int _h)
{
	jl::Globals::s_screenWidth = static_cast<jl::u32>(_w);
	jl::Globals::s_screenHeight = static_cast<jl::u32>(_h);

	m_sandbox.onWindowResized(jl::Globals::s_screenWidth, jl::Globals::s_screenHeight);

	glViewport(0, 0, _w, _h);
}

//-----------------------------------------------------------------------------

void AppGlWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_prerenderCommand)
	{
		m_prerenderCommand();
	}

	m_sandbox.draw();

	if (m_postrenderCommand)
	{
		m_postrenderCommand();
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyPressEvent(QKeyEvent* _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	LOG_INFO("Pressed key, keycode: {}", _event->nativeVirtualKey());
	jl::InputManager::getInstance().processKey(_event->nativeVirtualKey(), true);
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyReleaseEvent(QKeyEvent* _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	jl::InputManager::getInstance().processKey(_event->nativeVirtualKey(), false);
}

//-----------------------------------------------------------------------------

void AppGlWidget::update()
{
	const float dt = getDeltaTime();
	jl::Globals::s_timeTotal += dt;

	m_sandbox.update(dt);
	repaint();
}

//-----------------------------------------------------------------------------

float AppGlWidget::getDeltaTime()
{
	using namespace std::chrono;

	static auto s_lastTime = high_resolution_clock::now();
	const auto currentTime = high_resolution_clock::now();
	
	auto durationFloat = duration_cast<duration<float>>(currentTime - s_lastTime);
	s_lastTime = currentTime;

	return durationFloat.count();
}

//-----------------------------------------------------------------------------
