#include "ui/EditableVec3Widget.hpp"
#include "ui_EditableVec3Widget.h"

//-----------------------------------------------------------------------------

EditableVec3Widget::EditableVec3Widget(QWidget* _parent)
	: QWidget(_parent)
{
	m_ui = std::make_unique<Ui::EditableVec3Widget>();
	m_ui->setupUi(this);

	//connect(m_ui->dsb_x, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
	//connect(m_ui->dsb_y, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
	//connect(m_ui->dsb_z, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
}

//-----------------------------------------------------------------------------

QVector3D EditableVec3Widget::getValue() const noexcept
{
	return QVector3D{
		static_cast<float>(m_ui->dsb_x->value()),
		static_cast<float>(m_ui->dsb_y->value()),
		static_cast<float>(m_ui->dsb_z->value())
	};
}

//-----------------------------------------------------------------------------

void EditableVec3Widget::setValue(const QVector3D& _value) noexcept
{
	m_value = _value;

	m_ui->dsb_x->setValue(m_value.x());
	m_ui->dsb_y->setValue(m_value.y());
	m_ui->dsb_z->setValue(m_value.z());
}

//-----------------------------------------------------------------------------

void EditableVec3Widget::onValueChanged()
{
}

//-----------------------------------------------------------------------------
