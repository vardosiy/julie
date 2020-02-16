#include "ui/MainWidget.hpp"
#include "ui_MainWidget.h"

#include "renderer/scene/Scene.hpp"
//#include "renderer/scene/Object.hpp"

#include <QStringListModel>
#include <QKeyEvent>
#include <fmt/format.h>

#include <cassert>

//-----------------------------------------------------------------------------

MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::MainWidget>())
	, m_listModel(std::make_unique<QStringListModel>(this))
{
	m_ui->setupUi(this);
	m_ui->listv_objects->setModel(m_listModel.get());

	connect(m_ui->chb_fillPolygons, &QCheckBox::stateChanged, this, &MainWidget::chbFillPolygonsValueChanged);
}

//-----------------------------------------------------------------------------

MainWidget::~MainWidget() = default;

//-----------------------------------------------------------------------------

void MainWidget::refreshObjectsList(const std::vector<jl::s32>& _objects)
{
	QStringList list;

	fmt::memory_buffer buf;
	for (const jl::s32 id : _objects)
	{
		format_to(buf, "{}", id);
		list << buf.data();
	}

	m_listModel->setStringList(list);
}

//-----------------------------------------------------------------------------

void MainWidget::chbFillPolygonsValueChanged(int _state)
{
	DrawMode drawMode = DrawMode::Fill;

	switch (_state)
	{
		case Qt::CheckState::Checked:
		{
			drawMode = DrawMode::Fill;
		}
		break;

		case Qt::CheckState::PartiallyChecked:
		{
		}
		break;

		case Qt::CheckState::Unchecked:
		{
			drawMode = DrawMode::Edges;
		}
		break;

		default:
		{
			assert(0);
		}
	}

	m_ui->oglw_screen->setDrawMode(drawMode);
}

//-----------------------------------------------------------------------------
