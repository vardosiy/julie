#include "ui/properties/EditableResourcePathWidget.hpp"
#include "ui_EditableResourcePathWidget.h"

#include "julie/managers/ResourceManager.hpp"

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

const QVariant& EditableResourcePathWidget::getValue() const noexcept
{
	const QString path = m_ui->text_path->text();

	if (m_value.canConvert<ModelUiWrapper>())
	{
		jl::Model* model = nullptr;
		if (!path.isEmpty())
		{
			model = jl::ResourceManager::getInstance().loadModel(path.toStdString(), true /* _loadMaterials */);
		}
		m_value = QVariant::fromValue(ModelUiWrapper{ path, model });
	}
	else if (m_value.canConvert<TextureUiWrapper>())
	{
		jl::Texture* texture = nullptr;
		if (!path.isEmpty())
		{
			texture = jl::ResourceManager::getInstance().loadTexture(path.toStdString());
		}
		m_value = QVariant::fromValue(TextureUiWrapper{ path, texture });
	}
	else if (m_value.canConvert<ShaderUiWrapper>())
	{
		jl::Shader* shader = nullptr;
		if (!path.isEmpty())
		{
			shader = jl::ResourceManager::getInstance().loadShader(path.toStdString());
		}
		m_value = QVariant::fromValue(ShaderUiWrapper{ path, shader });
	}

	return m_value;
}

//-----------------------------------------------------------------------------

void EditableResourcePathWidget::setValue(const ModelUiWrapper& _value) noexcept
{
	m_value = QVariant::fromValue(_value);
	m_ui->text_path->setText(_value.filePath);
}

//-----------------------------------------------------------------------------

void EditableResourcePathWidget::setValue(const TextureUiWrapper& _value) noexcept
{
	m_value = QVariant::fromValue(_value);
	m_ui->text_path->setText(_value.filePath);
}

//-----------------------------------------------------------------------------

void EditableResourcePathWidget::setValue(const ShaderUiWrapper& _value) noexcept
{
	m_value = QVariant::fromValue(_value);
	m_ui->text_path->setText(_value.filePath);
}

//-----------------------------------------------------------------------------

void EditableResourcePathWidget::onOpenFilePressed()
{
	// TERRIBLE HACK TO AVOID CRASHING
	// https://stackoverflow.com/questions/38456378/crash-when-calling-getopenfilename-from-qitemdelegates-custom-editor
	m_ui->btn_openFile->setFocus();

	QString path;
	if (m_value.canConvert<ModelUiWrapper>())
	{
		path = selectFile("Select Model", "Models (*.nfg *.obj)");
	}
	else if (m_value.canConvert<TextureUiWrapper>())
	{
		path = selectFile("Select Texture", "Textures (*.png *.jpg *.tga)");
	}
	else if (m_value.canConvert<ShaderUiWrapper>())
	{
		path = selectFile("Select Shader", "Shader Data (*.shdata)");
	}
	m_ui->text_path->setText(path);
}

//-----------------------------------------------------------------------------

QString EditableResourcePathWidget::selectFile(const QString& _title, const QString& _filter)
{
	const QString fullPath = QFileDialog::getOpenFileName(this, _title, QDir::currentPath(), _filter);

	QString result;
	if (!fullPath.isEmpty())
	{
		QDir currentDir(QDir::currentPath());
		result = currentDir.relativeFilePath(fullPath);
	}
	return result;
}

//-----------------------------------------------------------------------------
