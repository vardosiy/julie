#include "ui/EditableVec4Widget.hpp"
#include "ui_EditableVec4Widget.h"

//-----------------------------------------------------------------------------

EditableVec4Widget::EditableVec4Widget(QWidget* _parent)
	: QWidget(_parent)
{
	m_ui = std::make_unique<Ui::EditableVec4Widget>();
	m_ui->setupUi(this);

	connect(m_ui->dsb_x, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
	connect(m_ui->dsb_y, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
	connect(m_ui->dsb_z, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
	connect(m_ui->dsb_w, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
}

//-----------------------------------------------------------------------------

const QVector4D& EditableVec4Widget::getValue() const noexcept
{
	return m_value;
}

//-----------------------------------------------------------------------------

void EditableVec4Widget::setValue(const QVector4D& _value) noexcept
{
	m_value = _value;

	m_ui->dsb_x->setValue(m_value.x());
	m_ui->dsb_y->setValue(m_value.y());
	m_ui->dsb_z->setValue(m_value.z());
	m_ui->dsb_w->setValue(m_value.w());
}

//-----------------------------------------------------------------------------

void EditableVec4Widget::onValueChanged()
{
	m_value = QVector4D{
		static_cast<float>(m_ui->dsb_x->value()),
		static_cast<float>(m_ui->dsb_y->value()),
		static_cast<float>(m_ui->dsb_z->value()),
		static_cast<float>(m_ui->dsb_w->value())
	};
}

//-----------------------------------------------------------------------------
