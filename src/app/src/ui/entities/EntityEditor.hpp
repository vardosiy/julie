//#pragma once
//
//#include "ui/IEntityActionHandler.hpp"
//
//#include <QWidget>
//#include <QItemSelection>
//#include <QStringList>
//#include <QStandardItemModel>
//
//#include <memory>
//#include <functional>
//
////-----------------------------------------------------------------------------
//
//namespace Ui {
//class EntitiesWidget;
//}
//
//namespace jl {
//class Material;
//}
//
//class SceneWrapper;
//
//class EntitiesWidget : public QWidget
//{
//	Q_OBJECT
//
////-----------------------------------------------------------------------------
//public:
//	explicit EntitiesWidget(QWidget* parent = nullptr);
//
//	void setScene(SceneWrapper* _sceneWrapper);
//	void setEntityActionHandler(IEntityActionHandler* _handler);
//
////-----------------------------------------------------------------------------
//private slots:
//	void onCurrentTabChanged(int _idx);
//
//	void onAddEntityBtnReleased();
//	void onDeleteEntityBtnReleased();
//
////-----------------------------------------------------------------------------
//private:
//	void onEntitySelected(const QItemSelection& _selection);
//
//	void addObject(const std::string& _name);
//	void addMaterial(const std::string& _name);
//
//	void deleteObject(const QString& _name);
//	void deleteMaterial(const QString& _name);
//	void deleteEntities(const QItemSelectionModel& _selectionModel, std::function<void(const QString&)>&& _deleteFun);
//
//	void replaceMaterialInAllMeshes(jl::Material* _old, jl::Material* _new);
//	void refreshMaterialsList();
//
//	std::string computeObjectName() const;
//	std::string computeMaterialName() const;
//	static std::string computeEntityName(
//		std::string_view _base,
//		std::function<bool(const std::string&)>&& _entityExistCheckFun
//	);
//
////-----------------------------------------------------------------------------
//	std::unique_ptr<Ui::EntitiesWidget> m_ui;
//
//	QStandardItemModel m_objectsModel;
//	QStandardItemModel m_materialsModel;
//
//	QStringList			m_objectsNamesList;
//	QStringList			m_materialsNamesList;
//
//	SceneWrapper* m_sceneWrapper;
//	IEntityActionHandler* m_actionHandler;
//
//	static constexpr std::string_view k_defaultObjectName = "Object_000";
//	static constexpr std::string_view k_defaultMaterialName = "Material_000";
//};
//
////-----------------------------------------------------------------------------
