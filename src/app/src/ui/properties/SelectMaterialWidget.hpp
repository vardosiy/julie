#pragma once

#include "ui/properties/PropertyTypes.hpp"

#include <QComboBox>

class SelectMaterialWidget : public QComboBox
{
	Q_OBJECT

public:
	explicit SelectMaterialWidget(QWidget* _parent = nullptr);

	const MaterialUiWrapper& getValue() const noexcept;
	void setValue(const MaterialUiWrapper& _value) noexcept;

private slots:
	void onMaterialChanged(const QString& _materialName);

private:
	MaterialUiWrapper m_value;
};
