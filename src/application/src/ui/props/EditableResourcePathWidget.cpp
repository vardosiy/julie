#include "ui/props/EditableResourcePathWidget.hpp"
#include "ui_EditableResourcePathWidget.h"

#include <QFileDialog>

//-----------------------------------------------------------------------------

EditableResourcePathWidget::EditableResourcePathWidget(QWidget* _parent)
	: QWidget(_parent)
{
	m_ui = std::make_unique<Ui::EditableResourcePathWidget>();
	m_ui->setupUi(this);

	connect(m_ui->btn_openFile, &QToolButton::pressed, this, &EditableResourcePathWidget::onOpenFilePressed);
}

//-----------------------------------------------------------------------------

QString EditableResourcePathWidget::getPath() const noexcept
{
	return m_ui->text_path->text();
}

//-----------------------------------------------------------------------------

void EditableResourcePathWidget::setPath(const QString& _path) noexcept
{
	return m_ui->text_path->setText(_path);
}

//-----------------------------------------------------------------------------

void EditableResourcePathWidget::onOpenFilePressed()
{
	// TERRIBLE HACK TO AVOID CRASHING
	// https://stackoverflow.com/questions/38456378/crash-when-calling-getopenfilename-from-qitemdelegates-custom-editor
	m_ui->btn_openFile->setFocus();

	const QString fullPath =
		QFileDialog::getOpenFileName(this, "Select Model", QDir::currentPath(), "Models (*.nfg *.obj *.dae)");

	if (!fullPath.isEmpty())
	{
		QDir currentDir(QDir::currentPath());
		const QString relativePath = currentDir.relativeFilePath(fullPath);
		m_ui->text_path->setText(relativePath);
	}
}

//-----------------------------------------------------------------------------
