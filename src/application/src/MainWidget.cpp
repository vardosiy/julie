#include <glad/glad.h>

#include "MainWidget.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/managers/SceneManager.hpp"
#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"

#include "renderer/shaders/Shader.hpp"

#include "utils/LogDefs.hpp"

#include <QKeyEvent>

#include <iostream>
#include <chrono>

//-----------------------------------------------------------------------------

MainWidget::MainWidget(QWidget * parent)
	: QOpenGLWidget(parent)
	, m_updateTimer(this)
{
}

//-----------------------------------------------------------------------------

void MainWidget::initializeGL()
{
	gladLoadGL();

	LOG_INFO(
		"OpenGL info\n\tVendor: {}\n\tRenderer: {}\n\tVersion: {}",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION)
	);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	jl::ResourceManager::getInstance().init();
	jl::SceneManager::getInstance().init();
	jl::EffectManager::getInstance().init();

	connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_updateTimer.start(1);
}

//-----------------------------------------------------------------------------

void MainWidget::resizeGL(int _w, int _h)
{
	jl::Globals::s_screenWidth = _w;
	jl::Globals::s_screenHeight = _h;
	glViewport(0, 0, _w, _h);
}

//-----------------------------------------------------------------------------

void MainWidget::paintGL()
{
	jl::EffectManager::getInstance().bindFbo();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	jl::SceneManager::getInstance().draw();
	jl::EffectManager::getInstance().apply();
}

//-----------------------------------------------------------------------------

void MainWidget::keyPressEvent(QKeyEvent * _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	LOG_INFO("Pressed key, keycode: {}", _event->nativeVirtualKey());
	jl::InputManager::getInstance().processKey(_event->nativeVirtualKey(), true);
}

//-----------------------------------------------------------------------------

void MainWidget::keyReleaseEvent(QKeyEvent * _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	jl::InputManager::getInstance().processKey(_event->nativeVirtualKey(), false);
}

//-----------------------------------------------------------------------------

void MainWidget::update()
{
	using namespace std::chrono;

	static auto s_lastTime = high_resolution_clock::now();
	const auto currentTime = high_resolution_clock::now();
	auto deltaTime = duration_cast<duration<float>>(currentTime - s_lastTime);

	jl::SceneManager::getInstance().update(deltaTime.count());
	jl::EffectManager::getInstance().update(deltaTime.count());

	repaint();

	jl::Globals::s_timeTotal += deltaTime.count();
	s_lastTime = currentTime;
}

//-----------------------------------------------------------------------------
