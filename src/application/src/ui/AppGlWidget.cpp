#include <glad/glad.h>

#include "ui/AppGlWidget.hpp"

#include "managers/InputManager.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Model.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"
#include "renderer/scene/Object.hpp"

#include "renderer/IntersectionsDetectionHelpers.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>
#include <QMouseEvent>

//-----------------------------------------------------------------------------

AppGlWidget::AppGlWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, m_scene(nullptr)
	, m_camera(nullptr)
	, m_drawBoundingBoxes(false)
{
}

//-----------------------------------------------------------------------------

AppGlWidget::~AppGlWidget()
{
	jl::Renderer::shutdown();
}

//-----------------------------------------------------------------------------

void AppGlWidget::setDrawMode(DrawMode _drawMode) noexcept
{
	jl::Renderer::PolygonMode frontPolygonsMode;
	jl::Renderer::PolygonMode backPolygonsMode;

	switch (_drawMode)
	{
	case DrawMode::Fill:
		{
			frontPolygonsMode = jl::Renderer::PolygonMode::Fill;
			backPolygonsMode = jl::Renderer::PolygonMode::Fill;
		}
		break;

	case DrawMode::Edges:
		{
			frontPolygonsMode = jl::Renderer::PolygonMode::Line;
			backPolygonsMode = jl::Renderer::PolygonMode::Line;
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
		jl::Renderer::setFrontPolygonsMode(jl::Renderer::PolygonMode::Fill);
		jl::Renderer::setBackPolygonsMode(jl::Renderer::PolygonMode::Fill);
	};
}

//-----------------------------------------------------------------------------

void AppGlWidget::drawBoundingBoxes(bool _val) noexcept
{
	m_drawBoundingBoxes = _val;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setScene(jl::Scene* _scene) noexcept
{
	m_scene = _scene;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setCamera(jl::Camera* _camera) noexcept
{
	m_camera = _camera;
}

//-----------------------------------------------------------------------------

app::Connection AppGlWidget::registerOnGlLoaded(const GlLoadedSignal::slot_type& _callback)
{
	return m_glLoadedSignal.connect(_callback);
}

//-----------------------------------------------------------------------------

void AppGlWidget::initializeGL()
{
	jl::Renderer::init();
	m_glLoadedSignal();
}

//-----------------------------------------------------------------------------

void AppGlWidget::resizeGL(int _w, int _h)
{
	jl::Globals::s_screenWidth = static_cast<jl::u32>(_w);
	jl::Globals::s_screenHeight = static_cast<jl::u32>(_h);

	const float fWidth = static_cast<float>(_w);
	const float fHeight = static_cast<float>(_h);
	m_camera->setAspect(fWidth / fHeight);

	glViewport(0, 0, _w, _h);
}

//-----------------------------------------------------------------------------

void AppGlWidget::paintGL()
{
	jl::Renderer::clear();

	if (m_scene && m_camera)
	{
		if (m_prerenderCommand)
		{
			m_prerenderCommand();
		}

		m_scene->render(*m_camera);

		if (m_postrenderCommand)
		{
			m_postrenderCommand();
		}
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyPressEvent(QKeyEvent* _event)
{
	if (!_event->isAutoRepeat())
	{
		LOG_INFO("Pressed key, keycode: {}", _event->nativeVirtualKey());
		InputManager::getInstance().keyPressed(_event->nativeVirtualKey());

		processKeyboardModifiers(_event->modifiers());
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyReleaseEvent(QKeyEvent* _event)
{
	if (!_event->isAutoRepeat())
	{
		InputManager::getInstance().keyReleased(_event->nativeVirtualKey());

		processKeyboardModifiers(_event->modifiers());
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::mousePressEvent(QMouseEvent* _event)
{
	const bool leftBtnPressed = _event->buttons() & Qt::MouseButton::LeftButton;
	if (m_selectedObject && leftBtnPressed && InputManager::getInstance().isCtrlPressed())
	{
		m_prevMousePos = calcWorldPosFromMouseClick(_event->pos(), *m_camera);
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::mouseReleaseEvent(QMouseEvent* _event)
{
	if (_event->button() == Qt::MouseButton::LeftButton)
	{
		if (m_scene && m_camera)
		{
			const jl::rayf mouseRay = calcRayFromMouseClick(_event->pos(), *m_camera);
			processObjectSelection(mouseRay);
		}

		m_prevMousePos = boost::none;
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::mouseMoveEvent(QMouseEvent* _event)
{
	if (m_prevMousePos && m_selectedObject && _event->buttons() & Qt::MouseButton::LeftButton)
	{
		const glm::vec3 clickPos = calcWorldPosFromMouseClick(_event->pos(), *m_camera);
		const glm::vec3 diff = clickPos - *m_prevMousePos;

		m_selectedObject->setPosition(m_selectedObject->getPosition() + diff);

		m_prevMousePos = clickPos;
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::wheelEvent(QWheelEvent* _event)
{
	if (m_selectedObject && InputManager::getInstance().isCtrlPressed())
	{
		const float scaleFactor = _event->angleDelta().y() > 0 ? 1.1f : 0.9f;

		const glm::vec3& originalScale = m_selectedObject->getScale();
		const glm::vec3 newScale = originalScale * scaleFactor;

		m_selectedObject->setScale(newScale);
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::processKeyboardModifiers(Qt::KeyboardModifiers _modifiers)
{
	int modifiers = InputManager::Modifiers::None;

	if (_modifiers & Qt::KeyboardModifier::ControlModifier)
	{
		modifiers |= InputManager::Modifiers::Ctrl;
	}
	if (_modifiers & Qt::KeyboardModifier::AltModifier)
	{
		modifiers |= InputManager::Modifiers::Alt;
	}
	if (_modifiers & Qt::KeyboardModifier::ShiftModifier)
	{
		modifiers |= InputManager::Modifiers::Shift;
	}

	InputManager::getInstance().setModifiers(static_cast<InputManager::Modifiers>(modifiers));
}

//-----------------------------------------------------------------------------

void AppGlWidget::processObjectSelection(const jl::rayf& _ray)
{
	m_selectedObject = nullptr;
	float distance = std::numeric_limits<float>::max();

	m_scene->forEachObject([&_ray, &distance, this](jl::Object& _object)
	{
		_object.setRenderFlags(jl::Object::RenderFlags::DrawModel);

		if (const jl::Model* _model = _object.getModel())
		{
			const jl::boxf boxWorld = _object.getWorldMatrix() * _model->getBoundingBox();

			float nearPos = 0.0f;
			float farPos = 0.0f;
			if (jl::intersects(boxWorld, _ray, nearPos, farPos) && nearPos < distance)
			{
				distance = nearPos;
				m_selectedObject = &_object;
			}
		}
	});

	if (m_selectedObject)
	{
		LOG_INFO("Selected object: {}", m_selectedObject->getName());
		m_selectedObject->setRenderFlags(jl::Object::RenderFlags::DrawAll);
	}
}

//-----------------------------------------------------------------------------

jl::rayf AppGlWidget::calcRayFromMouseClick(QPoint _pos, const jl::Camera& _camera)
{
	glm::vec4 rayClip(calcNormalizedClickPos(_pos, _camera), 1.0f);
	rayClip.z = -1.0f;

	glm::vec4 rayEye = glm::inverse(_camera.getProjectionMatrix()) * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

	const glm::vec3 rayWorld = glm::vec3(glm::inverse(_camera.getViewMatrix()) * rayEye);

	return jl::rayf{ _camera.getPosition(), glm::normalize(rayWorld) };
}

//-----------------------------------------------------------------------------

glm::vec3 AppGlWidget::calcWorldPosFromMouseClick(QPoint _pos, const jl::Camera& _camera)
{
	glm::vec4 posClip(calcNormalizedClickPos(_pos, _camera), 1.0f);

	glm::vec4 posEye = glm::inverse(_camera.getProjectionMatrix()) * posClip;
	posEye = glm::vec4(posEye.x, posEye.y, 0.0, 0.0);

	return glm::vec3(glm::inverse(_camera.getViewMatrix()) * posEye);
}

//-----------------------------------------------------------------------------

glm::vec3 AppGlWidget::calcNormalizedClickPos(QPoint _pos, const jl::Camera& _camera)
{
	const float normalisedX = 2.0f * _pos.x() / jl::Globals::s_screenWidth - 1.0f;
	const float normalisedY = 1.0f - 2.0f * _pos.y() / jl::Globals::s_screenHeight;

	return glm::vec3(normalisedX, normalisedY, 0.0f);
}

//-----------------------------------------------------------------------------
