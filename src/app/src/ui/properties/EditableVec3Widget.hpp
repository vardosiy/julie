#pragma once

#include "ui/properties/PropertyTypes.hpp"

#include <QWidget>
#include <QVariant>

namespace Ui {
class EditableVec3Widget;
}

class EditableVec3Widget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit EditableVec3Widget(QWidget* _parent = nullptr);

	const QVariant& getValue() const noexcept;
	void setValue(TransformVecUiWrapper _wrapper) noexcept;
	void setValue(ColorUiWrapper _wrapper) noexcept;

//-----------------------------------------------------------------------------
private slots:
	void onValueChanged();

//-----------------------------------------------------------------------------
private:
	void setupSpinBoxes(double _min, double _max, double _step, const glm::vec3& _value);
	
//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::EditableVec3Widget> m_ui;

	QVariant m_value;
	bool m_editingValue;
};
