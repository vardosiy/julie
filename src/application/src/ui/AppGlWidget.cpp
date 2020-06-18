#include <glad/glad.h>

#include "ui/AppGlWidget.hpp"

#include "data/SceneWrapper.hpp"
#include "data/ObjectWrapper.hpp"

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
	, m_sceneWrapper(nullptr)
	, m_camera(nullptr)
	, m_actionHandler(nullptr)
	, m_selectedObject(nullptr)
	, m_selectedObjDistance(0.0f)
{
}

//-----------------------------------------------------------------------------

AppGlWidget::~AppGlWidget()
{
	jl::Renderer::shutdown();
}

//-----------------------------------------------------------------------------

void AppGlWidget::makeContextCurrent()
{
	makeCurrent();
}

//-----------------------------------------------------------------------------

void AppGlWidget::setDrawMode(DrawMode _drawMode) noexcept
{
	const auto polygonsMode =
		_drawMode == DrawMode::Edges ?
		jl::Renderer::PolygonMode::Line :
		jl::Renderer::PolygonMode::Fill;

	m_prerenderCommand = [polygonsMode]()
	{
		jl::Renderer::setFrontPolygonsMode(polygonsMode);
		jl::Renderer::setBackPolygonsMode(polygonsMode);
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
	m_sceneWrapper->forEachObject([_val](ObjectWrapper& _objWrapper)
	{
		const jl::s32 flags = _val ?
			_objWrapper.getRenderFlags() | jl::Object::RenderFlags::DrawBoundingBox :
			_objWrapper.getRenderFlags() & ~jl::Object::RenderFlags::DrawBoundingBox;

		_objWrapper.setRenderFlags(flags);
	});
}

//-----------------------------------------------------------------------------

void AppGlWidget::setCamera(jl::Camera* _camera) noexcept
{
	m_camera = _camera;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setScene(SceneWrapper* _sceneWrapper) noexcept
{
	m_sceneWrapper = _sceneWrapper;
	refreshIntersections();
}

//-----------------------------------------------------------------------------

void AppGlWidget::setActionHandler(IEntityActionHandler* _handler) noexcept
{
	m_actionHandler = _handler;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setUninteractibleObjectName(const std::string& _objName) noexcept
{
	m_uninteractibleObjName = _objName;
}

//-----------------------------------------------------------------------------

void AppGlWidget::resetSelectedObj()
{
	m_sceneWrapper->forEachObject([](ObjectWrapper& _objWrapper)
	{
		const jl::s32 flags = _objWrapper.getRenderFlags() & ~jl::Object::RenderFlags::IsSelected;
		_objWrapper.setRenderFlags(flags);
	});

	m_selectedObject = nullptr;
	m_selectedObjDistance = std::numeric_limits<float>::max();
}

//-----------------------------------------------------------------------------

void AppGlWidget::refreshIntersections()
{
	if (!m_sceneWrapper)
	{
		return;
	}

	m_sceneWrapper->forEachObject([](ObjectWrapper& _objWrapper)
	{
		const jl::s32 flags = _objWrapper.getRenderFlags() & ~jl::Object::RenderFlags::IsIntersected;
		_objWrapper.setRenderFlags(flags);
	});

	checkIntersectionsWithRoom();

	m_sceneWrapper->forEachObject([this](ObjectWrapper& _i)
	{
		if (_i.getModel() == nullptr ||
			_i.getName() == m_uninteractibleObjName ||
			_i.getRenderFlags() & jl::Object::RenderFlags::IsIntersected)
			return;

		const jl::boxf worldBoxI = _i.getWorldMatrix() * _i.getModel()->getBoundingBox();
		m_sceneWrapper->forEachObject([this, &_i, &worldBoxI](ObjectWrapper& _j)
		{
			if (&_j == &_i ||
				_j.getModel() == nullptr ||
				_j.getName() == m_uninteractibleObjName)
				return;

			const jl::boxf worldBoxJ = _j.getWorldMatrix() * _j.getModel()->getBoundingBox();
			if (jl::intersect(worldBoxI, worldBoxJ))
			{
				_i.setRenderFlags(_i.getRenderFlags() | jl::Object::RenderFlags::IsIntersected);
				_j.setRenderFlags(_j.getRenderFlags() | jl::Object::RenderFlags::IsIntersected);
			}
		});
	});
}

//-----------------------------------------------------------------------------

void AppGlWidget::checkIntersectionsWithRoom()
{
	const ObjectWrapper* roomObj = m_sceneWrapper->findObject(m_uninteractibleObjName);
	const glm::vec3 roomSize = roomObj->getSize();

	std::array<jl::boxf, 5> wallsBbs;
	wallsBbs[0].min = glm::vec3(0.0f,		0.0f,		0.0f);
	wallsBbs[0].max = glm::vec3(roomSize.x,	roomSize.y,	0.0f);
	wallsBbs[1].min = glm::vec3(0.0f,		0.0f,		roomSize.z);
	wallsBbs[1].max = glm::vec3(roomSize.x,	roomSize.y,	roomSize.z);
	wallsBbs[2].min = glm::vec3(0.0f,		0.0f,		0.0f);
	wallsBbs[2].max = glm::vec3(0.0f,		roomSize.y,	roomSize.z);
	wallsBbs[3].min = glm::vec3(roomSize.x,	0.0f,		0.0f);
	wallsBbs[3].max = glm::vec3(roomSize.x,	roomSize.y,	roomSize.z);
	wallsBbs[4].min = glm::vec3(0.0f,		0.0f,		0.0f);
	wallsBbs[4].max = glm::vec3(roomSize.x,	0.0f,		roomSize.z);

	m_sceneWrapper->forEachObject([this, &wallsBbs](ObjectWrapper& _i)
	{
		if (_i.getModel() == nullptr ||
			_i.getName() == m_uninteractibleObjName ||
			_i.getRenderFlags() & jl::Object::RenderFlags::IsIntersected)
			return;

		const jl::boxf worldBox = _i.getWorldMatrix() * _i.getModel()->getBoundingBox();
		for (const jl::boxf& box : wallsBbs)
		{
			if (jl::intersect(worldBox, box))
			{
				_i.setRenderFlags(_i.getRenderFlags() | jl::Object::RenderFlags::IsIntersected);
				break;
			}
		}
	});
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.0f);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_sceneWrapper && m_camera)
	{
		if (m_prerenderCommand)
		{
			m_prerenderCommand();
		}

		m_sceneWrapper->render(*m_camera);

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
		if (m_sceneWrapper && m_camera)
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
		const glm::vec3 diff = (clickPos - *m_prevMousePos) * m_selectedObjDistance;

		m_selectedObject->setPosition(m_selectedObject->getPosition() + diff);

		m_prevMousePos = clickPos;
		m_actionHandler->onObjectMoved(*m_selectedObject);
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::wheelEvent(QWheelEvent* _event)
{
	if (m_selectedObject && InputManager::getInstance().isCtrlPressed())
	{
		const float scaleFactor = _event->angleDelta().y() > 0 ? 1.1f : 0.9f;

		const glm::vec3& originalScale = m_selectedObject->getSize();
		const glm::vec3 newScale = originalScale * scaleFactor;

		m_selectedObject->setSize(newScale);
		m_actionHandler->onObjectScaled(*m_selectedObject);
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
	resetSelectedObj();

	m_sceneWrapper->forEachObject([&_ray, this](ObjectWrapper& _objWrapper)
	{
		if (m_uninteractibleObjName == _objWrapper.getName())
			return;

		if (const jl::Model* _model = _objWrapper.getModel())
		{
			const jl::boxf boxWorld = _objWrapper.getWorldMatrix() * _model->getBoundingBox();

			float nearPos = 0.0f;
			float farPos = 0.0f;
			if (jl::intersects(boxWorld, _ray, nearPos, farPos) && nearPos < m_selectedObjDistance)
			{
				m_selectedObject = &_objWrapper;
				m_selectedObjDistance = nearPos;
			}
		}
	});

	if (m_selectedObject)
	{
		LOG_INFO("Selected object: {}", m_selectedObject->getName());

		const jl::s32 flags = m_selectedObject->getRenderFlags() | jl::Object::RenderFlags::IsSelected;
		m_selectedObject->setRenderFlags(flags);

		if (m_actionHandler)
		{
			m_actionHandler->objectSelected(*m_selectedObject);
		}
	}
}

//-----------------------------------------------------------------------------

jl::rayf AppGlWidget::calcRayFromMouseClick(QPoint _pos, const jl::Camera& _camera)
{
	glm::vec4 rayClip = glm::vec4(calcNormalizedClickPos(_pos, _camera), 1.0f);
	rayClip.z = -1.0f;

	glm::vec4 rayEye = glm::inverse(_camera.getProjectionMatrix()) * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

	const glm::vec3 rayWorld = glm::vec3(glm::inverse(_camera.getViewMatrix()) * rayEye);

	return jl::rayf{ _camera.getPosition(), glm::normalize(rayWorld) };
}

//-----------------------------------------------------------------------------

glm::vec3 AppGlWidget::calcWorldPosFromMouseClick(QPoint _pos, const jl::Camera& _camera)
{
	glm::vec4 posClip = glm::vec4(calcNormalizedClickPos(_pos, _camera), 1.0f);
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
