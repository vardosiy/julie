#pragma once

#include <QWidget>
#include <QStandardItemModel>

#include <memory>
#include <variant>

namespace Ui {
class PropertiesWidget;
}

namespace jl {
class Object;
class Material;
}

//-----------------------------------------------------------------------------

class PropertiesWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit PropertiesWidget(QWidget* parent = nullptr);

	void setActiveEntity(jl::Object& _object);
	void setActiveEntity(jl::Material& _material);
	void reset();

//-----------------------------------------------------------------------------
private:
	template<typename T>
	void setPropValue(int _idx, const QString& _name, const T& _value);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::PropertiesWidget> m_ui;

	QStandardItemModel m_propertiesTableModel;

	std::variant<jl::Object*, jl::Material*, std::nullptr_t> m_activeEntity;

	static const QString k_objectPropModel;
	static const QString k_objectPropMaterial;
};

//-----------------------------------------------------------------------------
