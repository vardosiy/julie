#include <glad/glad.h>

#include "ui/AppGlWidget.hpp"

#include "managers/InputManager.hpp"

#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "julie/Globals.hpp"
#include "julie/Renderer.hpp"
#include "julie/Model.hpp"
#include "julie/scene/Scene.hpp"
#include "julie/scene/Camera.hpp"

#include "julie/IntersectionsDetectionHelpers.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>
#include <QMouseEvent>

//-----------------------------------------------------------------------------

AppGlWidget::AppGlWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, m_camera(nullptr)
	, m_scene(nullptr)
	, m_actionHandler(nullptr)
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

void AppGlWidget::setCamera(jl::Camera* _camera) noexcept
{
	m_camera = _camera;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setScene(jl::Scene* _scene) noexcept
{
	m_scene = _scene;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setActionHandler(IEntityActionHandler* _handler) noexcept
{
	m_actionHandler = _handler;
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

	initScene();
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
		LOG_INFO("[AppGlWidget] Pressed key, keycode: {}", _event->nativeVirtualKey());
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

std::unique_ptr<jl::Model> model;
void AppGlWidget::initScene()
{
	ResourceManager& resourceMgr = ResourceManager::getInstance();
	MaterialsManager& materialsMgr = MaterialsManager::getInstance();

	jl::Texture* texture = resourceMgr.loadTexture("res/textures/ULW1541_10453.jpg");
	ASSERT(texture);
	jl::Shader* shader = resourceMgr.loadShader("res/shaders/composed/SimpleTexture.shdata");
	ASSERT(shader);

	jl::Material& material = materialsMgr.createMaterial("material");
	material.setShader(shader);
	material.setProperty("u_texture2D", texture);
	material.setProperty("u_color", glm::vec4{ 1.0f });

	std::vector<jl::Vertex> vertices(4);
	vertices[0].pos = glm::vec3(-1.0f, -1.0f, 0.0f);
	vertices[1].pos = glm::vec3(-1.0f,  1.0f, 0.0f);
	vertices[2].pos = glm::vec3( 1.0f, -1.0f, 0.0f);
	vertices[3].pos = glm::vec3( 1.0f,  1.0f, 0.0f);
	vertices[0].uv = glm::vec2(0.0f, 0.0f);
	vertices[1].uv = glm::vec2(0.0f, 1.0f);
	vertices[2].uv = glm::vec2(1.0f, 0.0f);
	vertices[3].uv = glm::vec2(1.0f, 1.0f);
	std::vector<jl::index_t> indecies = {
		0, 1, 2,
		1, 2, 3
	};

	model = std::make_unique<jl::Model>(vertices, indecies);
	model->getMesh(0).setMaterial(&material);

	jl::ecs::Entity& entity = m_scene->createEntity("some_name");
	entity.addComponent<ModelComponent>(model.get());
	TransformComponent* a = entity.getComponent<TransformComponent>();
	a->pos = glm::vec3{ 0.0f, 0.0f, -1.0f };
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
