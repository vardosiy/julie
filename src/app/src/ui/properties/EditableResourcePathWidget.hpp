#pragma once

#include "ui/MetaTypes.hpp"

#include <QWidget>
#include <QVariant>

namespace Ui {
class EditableResourcePathWidget;
}

class EditableResourcePathWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit EditableResourcePathWidget(QWidget* _parent = nullptr);

	const QVariant& getValue() const noexcept;
	void setValue(const ModelUiWrapper& _value) noexcept;
	void setValue(const TextureUiWrapper& _value) noexcept;
	void setValue(const ShaderUiWrapper& _value) noexcept;

//-----------------------------------------------------------------------------
private slots:
	void onOpenFilePressed();

//-----------------------------------------------------------------------------
private:
	QString selectFile(const QString& _title, const QString& _filter);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::EditableResourcePathWidget> m_ui;

	mutable QVariant m_value;
};
