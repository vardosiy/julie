#pragma once

#include "ui/props/PropertyTypes.hpp"

#include <QComboBox>

class EditMaterialsWidget : public QComboBox
{
	Q_OBJECT

public:
	explicit EditMaterialsWidget(QWidget* _parent = nullptr);

	MaterialUiWrapper getData() const noexcept;
	void setData(MaterialUiWrapper _data) noexcept;
};
