#include "ui/ViewPropertiesWidget.hpp"
#include "ui/AppGlWidget.hpp"
#include "ui/UiUtils.hpp"
#include "ui_ViewPropertiesWidget.h"

#include "controllers/FreeflyCameraController.hpp"

#include "renderer/scene/Camera.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace details
{

struct ScopedFlagSwitcher
{
	ScopedFlagSwitcher(bool& _val)
		: m_value(_val)
	{
		m_value = !m_value;
	}

	~ScopedFlagSwitcher()
	{
		m_value = !m_value;
	}

	bool& m_value;
};

} // namespace details

//-----------------------------------------------------------------------------

ViewPropertiesWidget::ViewPropertiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_glWidget(nullptr)
	, m_camController(nullptr)
	, m_editingValue(false)
{
	m_ui = std::make_unique<Ui::ViewPropertiesWidget>();
	m_ui->setupUi(this);

	connect(m_ui->chb_showBb, &QCheckBox::stateChanged, [this](int _value) { m_glWidget->drawBoundingBoxes(_value == Qt::CheckState::Checked); });
	connect(m_ui->chb_fillPolygons, &QCheckBox::stateChanged, this, &ViewPropertiesWidget::onFillPolygonsValueChanged);

	connect(m_ui->sld_camMoveSpeed, &QSlider::valueChanged, this, qOverload<int>(&ViewPropertiesWidget::onCamMoveSpeedChanged));
	connect(m_ui->sld_camRotateSpeed, &QSlider::valueChanged, this, qOverload<int>(&ViewPropertiesWidget::onCamRotateSpeedChanged));

	connect(m_ui->dsb_camMoveSpeed, qOverload<double>(&QDoubleSpinBox::valueChanged), this, qOverload<float>(&ViewPropertiesWidget::onCamMoveSpeedChanged));
	connect(m_ui->dsb_camRotateSpeed, qOverload<double>(&QDoubleSpinBox::valueChanged), this, qOverload<float>(&ViewPropertiesWidget::onCamRotateSpeedChanged));
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::update(float _dt) noexcept
{
	m_camController->update(_dt);

	const jl::Camera* camera = m_camController->getCamera();
	m_ui->lbl_camPosValue->setText(vecToString(camera->getPosition()));
	m_ui->lbl_camViewDirectionValue->setText(vecToString(camera->getViewTarget()));
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::setGlWidget(AppGlWidget* _glWidget) noexcept
{
	m_glWidget = _glWidget;
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::setCameraController(FreeflyCameraController* _camContoller) noexcept
{
	details::ScopedFlagSwitcher switcher(m_editingValue);

	m_camController = _camContoller;

	const float camMoveSpeed = m_camController->getCameraMoveSpeed();
	const float camRotateSpeed = m_camController->getCameraRotateSpeed();

	m_ui->dsb_camMoveSpeed->setValue(camMoveSpeed);
	m_ui->dsb_camRotateSpeed->setValue(camRotateSpeed);

	m_ui->sld_camMoveSpeed->setValue(static_cast<int>(camMoveSpeed * 100.0f));
	m_ui->sld_camRotateSpeed->setValue(static_cast<int>(camRotateSpeed * 100.0f));
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::onCamMoveSpeedChanged(int _value)
{
	if (!m_editingValue)
	{
		details::ScopedFlagSwitcher switcher(m_editingValue);

		const float newValue = static_cast<float>(_value) * 0.01f;
		m_camController->setCameraMoveSpeed(newValue);
		m_ui->dsb_camMoveSpeed->setValue(newValue);
	}
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::onCamRotateSpeedChanged(int _value)
{
	if (!m_editingValue)
	{
		details::ScopedFlagSwitcher switcher(m_editingValue);

		const float newValue = static_cast<float>(_value) * 0.01f;
		m_camController->setCameraRotateSpeed(newValue);
		m_ui->dsb_camRotateSpeed->setValue(newValue);
	}
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::onCamMoveSpeedChanged(float _value)
{
	if (!m_editingValue)
	{
		details::ScopedFlagSwitcher switcher(m_editingValue);

		m_camController->setCameraMoveSpeed(_value);
		m_ui->sld_camMoveSpeed->setValue(static_cast<int>(_value * 100.0f));
	}
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::onCamRotateSpeedChanged(float _value)
{
	if (!m_editingValue)
	{
		details::ScopedFlagSwitcher switcher(m_editingValue);

		m_camController->setCameraRotateSpeed(_value);
		m_ui->sld_camRotateSpeed->setValue(static_cast<int>(_value * 100.0f));
	}
}

//-----------------------------------------------------------------------------

void ViewPropertiesWidget::onFillPolygonsValueChanged(int _state)
{
	AppGlWidget::DrawMode drawMode = AppGlWidget::DrawMode::Fill;

	switch (_state)
	{
	case Qt::CheckState::Checked:
		drawMode = AppGlWidget::DrawMode::Fill;
		break;

	case Qt::CheckState::Unchecked:
		drawMode = AppGlWidget::DrawMode::Edges;
		break;

	default:
		ASSERT(0);
	}

	m_glWidget->setDrawMode(drawMode);
}

//-----------------------------------------------------------------------------
