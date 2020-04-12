#include <glad/glad.h>

#include "ui/AppGlWidget.hpp"

#include "CommonDefs.hpp"
#include "managers/InputManager.hpp"

#include "renderer/Renderer.hpp"
#include "renderer/Globals.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>

//-----------------------------------------------------------------------------

AppGlWidget::AppGlWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, m_scene(nullptr)
	, m_camera(0.00001f, 100.0f, 45.0f)
	, m_camMoveSpeed(1.0f)
	, m_camRotationSpeed(1.0f)
	, m_updateTimer(this)
{
}

//-----------------------------------------------------------------------------

void AppGlWidget::setDrawMode(DrawMode _drawMode) noexcept
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
			ASSERT(0);
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

void AppGlWidget::setCameraMoveSpeed(int _speed) noexcept
{
	m_camMoveSpeed = static_cast<float>(_speed) * 0.01f;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setCameraRotateSpeed(int _speed) noexcept
{
	m_camRotationSpeed = static_cast<float>(_speed) * 0.01f;
}

//-----------------------------------------------------------------------------

jl::Scene* AppGlWidget::getScene() noexcept
{
	return m_scene;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setScene(jl::Scene* _scene) noexcept
{
	m_scene = _scene;
}

//-----------------------------------------------------------------------------

app::Connection AppGlWidget::registerOnGlLoaded(const GlLoadedSignal::slot_type& _callback)
{
	return m_glLoadedSignal.connect(_callback);
}

//-----------------------------------------------------------------------------

void AppGlWidget::initializeGL()
{
	ASSERT(gladLoadGL());
	m_glLoadedSignal();

	LOG_INFO(
		"OpenGL info\n-> Vendor: {}\n-> Renderer: {}\n-> Version: {}",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION)
	);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_updateTimer.start(1);
}

//-----------------------------------------------------------------------------

void AppGlWidget::resizeGL(int _w, int _h)
{
	jl::Globals::s_screenWidth = static_cast<jl::u32>(_w);
	jl::Globals::s_screenHeight = static_cast<jl::u32>(_h);

	const float fWidth = static_cast<float>(_w);
	const float fHeight = static_cast<float>(_h);
	m_camera.setAspect(fWidth / fHeight);

	glViewport(0, 0, _w, _h);
}

//-----------------------------------------------------------------------------

void AppGlWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_scene)
	{
		if (m_prerenderCommand)
		{
			m_prerenderCommand();
		}

		m_scene->render(m_camera);

		if (m_postrenderCommand)
		{
			m_postrenderCommand();
		}
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
	InputManager::getInstance().processKey(_event->nativeVirtualKey(), true);
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyReleaseEvent(QKeyEvent* _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}
	InputManager::getInstance().processKey(_event->nativeVirtualKey(), false);
}

//-----------------------------------------------------------------------------

void AppGlWidget::update()
{
	const float dt = getDeltaTime();
	jl::Globals::s_timeTotal += dt;

	m_scene->update(dt);
	updateCameraPosition(dt);

	repaint();
}

//-----------------------------------------------------------------------------

float AppGlWidget::getDeltaTime()
{
	static TimePoint s_lastTime = Clock::now();
	const TimePoint currentTime = Clock::now();
	
	auto durationFloat = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - s_lastTime);
	s_lastTime = currentTime;

	return durationFloat.count();
}

//-----------------------------------------------------------------------------

void AppGlWidget::updateCameraPosition(float _dt) noexcept
{
	InputManager& inputMgr = InputManager::getInstance();

	glm::vec3 camTraslation(0.0f);
	const float movePoints = m_camMoveSpeed * _dt;
	camTraslation.x += inputMgr.isPressed('D') * movePoints;
	camTraslation.x -= inputMgr.isPressed('A') * movePoints;
	camTraslation.y += inputMgr.isPressed('R') * movePoints;
	camTraslation.y -= inputMgr.isPressed('F') * movePoints;
	camTraslation.z += inputMgr.isPressed('S') * movePoints;
	camTraslation.z -= inputMgr.isPressed('W') * movePoints;

	if (camTraslation != glm::vec3(0.0f))
	{
		m_camera.move(camTraslation);
	}

	glm::vec2 camRotation(0.0f);
	const float rotatePoints = m_camRotationSpeed * _dt;
	camRotation.y += inputMgr.isPressed(InputManager::Arrows::Left) * rotatePoints;
	camRotation.y -= inputMgr.isPressed(InputManager::Arrows::Right) * rotatePoints;
	camRotation.x += inputMgr.isPressed(InputManager::Arrows::Up) * rotatePoints;
	camRotation.x -= inputMgr.isPressed(InputManager::Arrows::Down) * rotatePoints;

	if (camRotation != glm::vec2(0.0f))
	{
		m_camera.rotate(camRotation);
	}

	m_camera.update();
}

//-----------------------------------------------------------------------------
