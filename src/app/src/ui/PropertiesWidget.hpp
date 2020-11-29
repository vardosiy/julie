#pragma once

#include <QWidget>
#include <QStandardItemModel>

#include <memory>
#include <variant>

//-----------------------------------------------------------------------------

namespace Ui {
class PropertiesWidget;
}

namespace jl {
class Model;
class Object;
class Material;
}

class PropertiesWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit PropertiesWidget(QWidget* parent = nullptr);

	void setActiveEntity(jl::Object& _object);
	void setActiveEntity(jl::Material& _material);
	void reset();

	void refreshObjectPos();
	void refreshObjectSize();

//-----------------------------------------------------------------------------
private:
	void refreshObjectProperties(jl::Object& _object);
	void refreshMeshes(jl::Model* _model, const QModelIndex& _parent);

	void refreshMaterialProperties(jl::Material& _material);
	void refreshUniforms(jl::Material& _material, const QModelIndex& _parent);

//-----------------------------------------------------------------------------
	void onDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles);
	void onObjectChanged(const QModelIndex& _idx, jl::Object& _object);
	void onMaterialChanged(const QModelIndex& _idx, jl::Material& _material);

//-----------------------------------------------------------------------------
	void setChildRowCount(int _rows, const QModelIndex& _parent);

	void setHeaderRow(int _row, const QString& _name, const QModelIndex& _parent = QModelIndex());
	void setPropertyRow(int _row, const QString& _name, const QVariant& _value, const QModelIndex& _parent = QModelIndex());
	void setCellValue(const QModelIndex& _idx, const QVariant& _value, bool _enableEditing);

	QModelIndex index(int _row, int _col, const QModelIndex& _parent = QModelIndex());

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::PropertiesWidget> m_ui;
	QStandardItemModel m_propertiesTableModel;

	std::variant<jl::Object*, jl::Material*, std::nullptr_t> m_activeEntity;

	static constexpr int k_nameColIdx = 0;
	static constexpr int k_valueColIdx = 1;

	static constexpr int k_transformsNum = 3;

	static constexpr int k_transformRowIdx = 1;
};

//-----------------------------------------------------------------------------
