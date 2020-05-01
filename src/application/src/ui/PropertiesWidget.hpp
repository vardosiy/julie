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

//-----------------------------------------------------------------------------
private:
	struct DataChangedHandleVisitor
	{
		void operator()(jl::Object* _object);
		void operator()(jl::Material* _material);
		void operator()(std::nullptr_t _null);

		int m_propIdx;
		const std::string& m_newValue;
	};

//-----------------------------------------------------------------------------
	void setTableCellValue(int _row, int _col, const QString& _value);

	void onDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::PropertiesWidget> m_ui;

	QStandardItemModel m_propertiesTableModel;

	std::variant<jl::Object*, jl::Material*, std::nullptr_t> m_activeEntity;

	static const QString k_objectPropModel;
	static const QString k_objectPropMaterial;

	static const QString k_columnHeaderPropName;
	static const QString k_columnHeaderPropValue;

	static constexpr int k_propNameIdx = 0;
	static constexpr int k_propValueIdx = 1;
};

//-----------------------------------------------------------------------------
