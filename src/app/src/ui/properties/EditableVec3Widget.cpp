#include "ui/properties/EditableVec3Widget.hpp"
#include "ui_EditableVec3Widget.h"

#include "ui/UiUtils.hpp"

//-----------------------------------------------------------------------------

EditableVec3Widget::EditableVec3Widget(QWidget* _parent)
	: QWidget(_parent)
	, m_editingValue(false)
{
	m_ui = std::make_unique<Ui::EditableVec3Widget>();
	m_ui->setupUi(this);

	m_ui->dsb_x->setDecimals(k_floatDecimals);
	m_ui->dsb_y->setDecimals(k_floatDecimals);
	m_ui->dsb_z->setDecimals(k_floatDecimals);

	connect(m_ui->dsb_x, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &EditableVec3Widget::onValueChanged);
	connect(m_ui->dsb_y, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &EditableVec3Widget::onValueChanged);
	connect(m_ui->dsb_z, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &EditableVec3Widget::onValueChanged);
}

//-----------------------------------------------------------------------------

const QVariant& EditableVec3Widget::getValue() const noexcept
{
	return m_value;
}

//-----------------------------------------------------------------------------

void EditableVec3Widget::setValue(TransformVecUiWrapper _wrapper) noexcept
{
	m_value = QVariant::fromValue(_wrapper);
	setupSpinBoxes(k_floatUiMin, k_floatUiMax, k_floatUiStep, _wrapper.value);
}

//-----------------------------------------------------------------------------

void EditableVec3Widget::setValue(ColorUiWrapper _wrapper) noexcept
{
	m_value = QVariant::fromValue(_wrapper);
	setupSpinBoxes(0.0, 1.0, 0.01, _wrapper.value);
}

//-----------------------------------------------------------------------------

void EditableVec3Widget::onValueChanged()
{
	if (m_editingValue)
	{
		return;
	}

	glm::vec3 value{
		static_cast<float>(m_ui->dsb_x->value()),
		static_cast<float>(m_ui->dsb_y->value()),
		static_cast<float>(m_ui->dsb_z->value())
	};

	if (m_value.canConvert<TransformVecUiWrapper>())
	{
		TransformVecUiWrapper transformValue = qvariant_cast<TransformVecUiWrapper>(m_value);
		transformValue.editCallback(value);
		transformValue.value = value;
		m_value = QVariant::fromValue(transformValue);
	}
	else if (m_value.canConvert<ColorUiWrapper>())
	{
		ColorUiWrapper colorValue = qvariant_cast<ColorUiWrapper>(m_value);
		colorValue.editCallback(value);
		colorValue.value = value;
		m_value = QVariant::fromValue(colorValue);
	}
}

//-----------------------------------------------------------------------------

void EditableVec3Widget::setupSpinBoxes(double _min, double _max, double _step, const glm::vec3& _value)
{
	m_ui->dsb_x->setSingleStep(_step);
	m_ui->dsb_y->setSingleStep(_step);
	m_ui->dsb_z->setSingleStep(_step);

	m_ui->dsb_x->setRange(_min, _max);
	m_ui->dsb_y->setRange(_min, _max);
	m_ui->dsb_z->setRange(_min, _max);

	ScopedFlagSwitcher switcher(m_editingValue);
	m_ui->dsb_x->setValue(_value.x);
	m_ui->dsb_y->setValue(_value.y);
	m_ui->dsb_z->setValue(_value.z);
}

//-----------------------------------------------------------------------------
