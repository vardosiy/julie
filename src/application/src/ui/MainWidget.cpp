#include "ui/MainWidget.hpp"
#include "ui_MainWidget.h"

#include "renderer/Renderer.hpp"
#include "renderer/scene/Scene.hpp"

#include <QKeyEvent>

#include <cassert>

//-----------------------------------------------------------------------------

MainWidget::MainWidget(QWidget * parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::MainWidget>())
{
	m_ui->setupUi(this);

	connect(m_ui->cd_fillPolygons, &QCheckBox::stateChanged, this, &MainWidget::cbFillPolygonsValueChanged);
}

//-----------------------------------------------------------------------------

MainWidget::~MainWidget() = default;

//-----------------------------------------------------------------------------

void MainWidget::cbFillPolygonsValueChanged(int _state)
{
	jl::PolygonMode frontPolygonsMode;
	jl::PolygonMode backPolygonsMode;

	switch (_state)
	{
		case Qt::CheckState::Checked:
		{
			frontPolygonsMode = jl::PolygonMode::Fill;
			backPolygonsMode = jl::PolygonMode::Fill;
		}
		break;

		case Qt::CheckState::PartiallyChecked:
		{
			frontPolygonsMode = jl::PolygonMode::Fill;
			backPolygonsMode = jl::PolygonMode::Line;
		}
		break;

		case Qt::CheckState::Unchecked:
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

	auto prerenderCommand = [frontPolygonsMode, backPolygonsMode]()
	{
		jl::Renderer::setFrontPolygonsMode(frontPolygonsMode);
		jl::Renderer::setBackPolygonsMode(backPolygonsMode);
	};
	jl::Scene::getInstance().setPrerenderCommand(prerenderCommand);

	auto postrenderCommand = []()
	{
		jl::Renderer::setFrontPolygonsMode(jl::PolygonMode::Fill);
		jl::Renderer::setBackPolygonsMode(jl::PolygonMode::Fill);
	};
	jl::Scene::getInstance().setPostrenderCommand(postrenderCommand);
}

//-----------------------------------------------------------------------------
