//#include "ui/EntitiesWidget.hpp"
//#include "ui_EntitiesWidget.h"
//
//#include "ui/entities/EntityDelegate.hpp"
//#include "ui/MetaTypes.hpp"
//
//#include "julie/managers/MaterialsManager.hpp"
//#include "julie/Material.hpp"
//#include "julie/Model.hpp"
//#include "julie/Mesh.hpp"
//
//#include "julie/scene/Scene.hpp"
//
//#include "utils/Utils.hpp"
//
////-----------------------------------------------------------------------------
//
//EntitiesWidget::EntitiesWidget(QWidget* parent)
//	: QWidget(parent)
//	, m_objectsModel(this)
//	, m_materialsModel(this)
//	, m_scene(nullptr)
//	, m_actionHandler(nullptr)
//{
//	m_ui = std::make_unique<Ui::EntitiesWidget>();
//	m_ui->setupUi(this);
//
//	m_ui->listv_objects->setModel(&m_objectsModel);
//	m_ui->listv_objects->setItemDelegateForColumn(0, new EntityDelegate(m_ui->listv_objects));
//
//	m_ui->listv_materials->setModel(&m_materialsModel);
//	m_ui->listv_materials->setItemDelegateForColumn(0, new EntityDelegate(m_ui->listv_materials));
//
//	connect(m_ui->btn_add,		&QPushButton::released,			this, &EntitiesWidget::onAddBtnReleased);
//	connect(m_ui->btn_delete,	&QPushButton::released,			this, &EntitiesWidget::onDeleteBtnReleased);
//	connect(m_ui->tabv_data,	&QTabWidget::currentChanged,	this, &EntitiesWidget::onCurrentTabChanged);
//
//	{
//		const QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
//		connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onItemSelected);
//	}
//	{
//		const QItemSelectionModel* selectionModel = m_ui->listv_materials->selectionModel();
//		connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onItemSelected);
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::setScene(jl::Scene* _scene)
//{
//	m_scene = _scene;
//
//	if (m_scene)
//	{
//		const int entitiesCount = static_cast<int>(m_scene->getEntitiesCount());
//		m_objectsModel.setRowCount(entitiesCount);
//
//		int counter = 0;
//		for (jl::EntityRef entity : *m_scene)
//		{
//			const QModelIndex idx = m_objectsModel.index(counter++, 0);
//			const QVariant data = QVariant::fromValue(EntityIdUiWrapper{ entity.getId() });
//			m_objectsModel.setData(idx, data);
//		}
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::setDefaultMaterial(jl::Material* _material)
//{
//	m_defaultMaterial = _material;
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::setEntityActionHandler(IEntityActionHandler* _handler)
//{
//	m_actionHandler = _handler;
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::onCurrentTabChanged(int _idx)
//{
//	const QWidget* currentTab = m_ui->tabv_data->widget(_idx);
//	if (currentTab == m_ui->tab_objects)
//	{
//		const QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
//		onItemSelected(selectionModel->selection());
//	}
//	else if (currentTab == m_ui->tab_materials)
//	{
//		refreshMaterialsList();
//
//		const QItemSelectionModel* selectionModel = m_ui->listv_materials->selectionModel();
//		onItemSelected(selectionModel->selection());
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::onAddBtnReleased()
//{
//	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while adding entity");
//	if (m_ui->tab_objects->isVisible())
//	{
//		ASSERT(m_scene);
//		if (m_scene)
//		{
//			addEntity(computeEntityName());
//		}
//	}
//	else if (m_ui->tab_materials->isVisible())
//	{
//		addMaterial(computeMaterialName());
//	}
//
//	if (m_actionHandler)
//	{
//		m_actionHandler->resetSelection();
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::addEntity(const std::string& _name)
//{
//	jl::EntityRef newEntity = m_scene->createEntity(_name);
//
//	QVariant value = QVariant::fromValue(EntityIdUiWrapper{ newEntity.getId() });
//	appendItemToModel(m_objectsModel, value);
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::addMaterial(const std::string& _name)
//{
//	jl::Material& material = jl::MaterialsManager::getInstance().createMaterial(_name);
//
//	if (m_defaultMaterial)
//	{
//		material = *m_defaultMaterial;
//	}
//
//	QVariant value = QVariant::fromValue(MaterialUiWrapper{ &material });
//	appendItemToModel(m_materialsModel, value);
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::appendItemToModel(QAbstractItemModel& _model, const QVariant& _value)
//{
//	_model.insertRow(_model.rowCount());
//
//	const QModelIndex idx = _model.index(_model.rowCount() - 1, 0);
//	_model.setData(idx, _value);
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::onDeleteBtnReleased()
//{
//	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while removing entity");
//	if (m_ui->tab_objects->isVisible())
//	{
//		auto deleteFun = std::bind(&EntitiesWidget::deleteEntity, this, std::placeholders::_1);
//		deleteItems(*m_ui->listv_objects->selectionModel(), deleteFun);
//	}
//	else if (m_ui->tab_materials->isVisible())
//	{
//		auto deleteFun = std::bind(&EntitiesWidget::deleteMaterial, this, std::placeholders::_1);
//		deleteItems(*m_ui->listv_materials->selectionModel(), deleteFun);
//	}
//
//	if (m_actionHandler)
//	{
//		m_actionHandler->resetSelection();
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::deleteEntity(const QModelIndex& _idx)
//{
//	jl::EntityRef entityToRemove = *m_scene->getEntity(_idx.row());
//	m_scene->removeEntity(entityToRemove.getId());
//
//	m_objectsModel.removeRow(_idx.row());
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::deleteMaterial(const QModelIndex& _idx)
//{
//	const MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_idx.data());
//
//	if (m_defaultMaterial != materialWrapper.value)
//	{
//		replaceMaterialInAllMeshes(materialWrapper.value, m_defaultMaterial);
//
//		jl::MaterialsManager::getInstance().deleteMaterial(*materialWrapper.value);
//		m_materialsModel.removeRow(_idx.row());
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::deleteItems(
//	const QItemSelectionModel& _selectionModel,
//	std::function<void(const QModelIndex&)>&& _deleteFun
//)
//{
//	const QModelIndexList indexList = _selectionModel.selectedIndexes();
//
//	ASSERT(std::is_sorted(indexList.begin(), indexList.end(), [](const QModelIndex& _lhs, const QModelIndex& _rhs)
//	{
//		return _lhs.row() < _rhs.row();
//	}));
//
//	std::for_each(indexList.rbegin(), indexList.rend(), [deleter = std::move(_deleteFun)](const QModelIndex& _idx)
//	{
//		deleter(_idx);
//	});
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::replaceMaterialInAllMeshes(jl::Material* _old, jl::Material* _new)
//{
//	if (!m_scene)
//	{
//		return;
//	}
//
//	//const int objectsCount = m_scene->getObjectsCount();
//	//for (int i = 0; i < objectsCount; ++i)
//	//{
//	//	if (jl::Model* model = m_scene->getObject(i).getModel())
//	//	{
//	//		const size_t meshesCount = model->getMeshesCount();
//	//		for (size_t i = 0; i < meshesCount; i++)
//	//		{
//	//			jl::Mesh& mesh = model->getMesh(i);
//
//	//			const jl::Material* meshMaterial = mesh.getMaterial();
//	//			if (meshMaterial == _old)
//	//			{
//	//				mesh.setMaterial(_new);
//	//			}
//	//		}
//	//	}
//	//}
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::refreshMaterialsList()
//{
//	jl::MaterialsManager& materialsMgr = jl::MaterialsManager::getInstance();
//	m_materialsModel.setRowCount(materialsMgr.getMaterialsCount());
//
//	int counter = 0;
//	materialsMgr.forEachMaterial([&counter, this](jl::Material& _material)
//	{
//		QVariant data = QVariant::fromValue(MaterialUiWrapper{ &_material });
//		m_materialsModel.setData(m_materialsModel.index(counter++, 0), data);
//	});
//}
//
////-----------------------------------------------------------------------------
//
//void EntitiesWidget::onItemSelected(const QItemSelection& _selection)
//{
//	ASSERT(m_actionHandler);
//	if (!m_actionHandler)
//	{
//		return;
//	}
//
//	const QModelIndexList indexList = _selection.indexes();
//	if (indexList.size() == 1)
//	{
//		const QModelIndex& idx = indexList.back();
//
//		ASSERT(idx.data().canConvert<EntityIdUiWrapper>() || idx.data().canConvert<MaterialUiWrapper>());
//		if (idx.data().canConvert<EntityIdUiWrapper>())
//		{
//			const EntityIdUiWrapper entityIdWrapper = qvariant_cast<EntityIdUiWrapper>(idx.data());
//			m_actionHandler->entitySelected(entityIdWrapper.value);
//		}
//		else if (idx.data().canConvert<MaterialUiWrapper>())
//		{
//			MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(idx.data());
//			m_actionHandler->materialSelected(*materialWrapper.value);
//		}
//	}
//	else
//	{
//		m_actionHandler->resetSelection();
//	}
//}
//
////-----------------------------------------------------------------------------
//
//std::string EntitiesWidget::computeEntityName() const
//{
//	return computeItemName(k_defaultObjectName, [this](const std::string& _name)
//	{
//		auto it = std::find_if(m_scene->begin(), m_scene->end(), [&_name](const jl::EntityRef _entity)
//		{
//			const TagComponent* tagCmpnt = _entity.getComponent<TagComponent>();
//			return tagCmpnt->tag == _name;
//		});
//		return it != m_scene->end();
//	});
//}
//
////-----------------------------------------------------------------------------
//
//std::string EntitiesWidget::computeMaterialName() const
//{
//	return computeItemName(k_defaultMaterialName, [](const std::string& _name)
//	{
//		return jl::MaterialsManager::getInstance().findMaterial(_name) != nullptr;
//	});
//}
//
////-----------------------------------------------------------------------------
//
//std::string EntitiesWidget::computeItemName(
//	std::string_view _base,
//	std::function<bool(const std::string&)>&& _entityExistCheckFun
//)
//{
//	std::string result = _base.data();
//	int counter = 0;
//
//	while (_entityExistCheckFun(result))
//	{
//		fmt::memory_buffer buf;
//		format_to(buf, "{:03d}", ++counter);
//
//		const size_t offset = result.length() - 3;
//		result.replace(offset, 3, buf.data(), 3); // last param need due to MSVC bug
//	}
//
//	return result;
//}
//
////-----------------------------------------------------------------------------
