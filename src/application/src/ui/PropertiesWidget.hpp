#pragma once

#include <QWidget>
#include <QStandardItemModel>

#include <boost/optional.hpp>

#include <memory>
#include <variant>

//-----------------------------------------------------------------------------

namespace Ui {
class PropertiesWidget;
}

namespace jl {
class Model;
class Material;
}

class ObjectWrapper;

class PropertiesWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit PropertiesWidget(QWidget* parent = nullptr);

	void setActiveEntity(ObjectWrapper& _object);
	void setActiveEntity(jl::Material& _material);
	void reset();

	void refreshObjectPos();
	void refreshObjectSize();

//-----------------------------------------------------------------------------
private:
	void refreshObjectProperties(const ObjectWrapper& _object);
	void refreshMeshes(jl::Model* _model);

	void refreshMaterialProperties(const jl::Material& _material);

	void onDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles);
	void onObjectChanged(const QModelIndex& _idx, ObjectWrapper& _object);

	void setHeaderRow(int _row, const QModelIndex& _parent, const QString& _name);
	void setPropertyRow(int _row, const QModelIndex& _parent, const QString& _name, const QVariant& _value, bool _editable);
	void setCellValue(const QModelIndex& _idx, const QVariant& _value, bool _enableEditing);

	QModelIndex index(int _row, int _col, const QModelIndex& _parent);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::PropertiesWidget> m_ui;

	QStandardItemModel m_propertiesTableModel;

	std::variant<ObjectWrapper*, jl::Material*, std::nullptr_t> m_activeEntity;

	static constexpr int k_nameColIdx = 0;
	static constexpr int k_valueColIdx = 1;

	static constexpr int k_modelRowIdx = 0;
	static constexpr int k_transformRowIdx = 1;
};

//-----------------------------------------------------------------------------
