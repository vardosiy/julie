#include <glad/glad.h>

#include "MainWidget.hpp"
#include "InputManager.hpp"

#include "renderer/common/Globals.hpp"

#include "renderer/scene/SceneManager.hpp"
#include "renderer/scene/ResourceManager.hpp"

#include "renderer/shaders/Shader.hpp"
#include "renderer/gl_primitives/textures/Texture.hpp"

#include "utils/LogDefs.hpp"

#include <QOpenGLTexture>
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

	LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::getInstance().init();
	SceneManager::getInstance().init();

	connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_updateTimer.start(1);
}

//-----------------------------------------------------------------------------

void MainWidget::resizeGL(int _w, int _h)
{
	Globals::s_screenWidth = _w;
	Globals::s_screenHeight = _h;
	//const float aspect = static_cast<float>(_w) / static_cast<float>(_h);
	//
	//m_projectionMatrix.setToIdentity();
	//m_projectionMatrix.perspective(45.0f, aspect, 0.01f, 100.f);
}

//-----------------------------------------------------------------------------

void MainWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::getInstance().draw();
}

//-----------------------------------------------------------------------------

void MainWidget::keyPressEvent(QKeyEvent * _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	LOG_INFO("Pressed key, keycode: {}", _event->nativeVirtualKey());
	InputManager::getInstance().processKey(static_cast<Qt::Key>(_event->nativeVirtualKey()), true);
}

//-----------------------------------------------------------------------------

void MainWidget::keyReleaseEvent(QKeyEvent * _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	InputManager::getInstance().processKey(static_cast<Qt::Key>(_event->nativeVirtualKey()), false);
}

//-----------------------------------------------------------------------------

void MainWidget::update()
{
	using namespace std::chrono;

	static auto s_lastTime = high_resolution_clock::now();
	const auto currentTime = high_resolution_clock::now();
	auto deltaTime = duration_cast<duration<float>>(currentTime - s_lastTime);

	SceneManager::getInstance().update(deltaTime.count());

	repaint();

	Globals::s_timeTotal += deltaTime.count();
	s_lastTime = currentTime;
}

//-----------------------------------------------------------------------------
