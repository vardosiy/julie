#pragma once

#include "ui/props/PropertyTypes.hpp"

#include <QComboBox>

class EditMaterialsWidget : public QComboBox
{
	Q_OBJECT

public:
	explicit EditMaterialsWidget(QWidget* _parent = nullptr);

	const MaterialUiWrapper& getData() const noexcept;
	void setData(const MaterialUiWrapper& _data) noexcept;

private slots:
	void onMaterialChanged(const QString& _materialName);

private:
	MaterialUiWrapper m_data;
};
