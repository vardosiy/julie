#include "ui/EntitiesWidget.hpp"
#include "ui_EntitiesWidget.h"

#include "ui/entities/EntityDelegate.hpp"
#include "ui/MetaTypes.hpp"

#include "julie/managers/MaterialsManager.hpp"
#include "julie/Material.hpp"
#include "julie/Model.hpp"
#include "julie/Mesh.hpp"

#include "julie/scene/Scene.hpp"
#include "julie/scene/Object.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

EntitiesWidget::EntitiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_objectsModel(this)
	, m_materialsModel(this)
	, m_scene(nullptr)
	, m_actionHandler(nullptr)
{
	m_ui = std::make_unique<Ui::EntitiesWidget>();
	m_ui->setupUi(this);

	m_ui->listv_objects->setModel(&m_objectsModel);
	m_ui->listv_objects->setItemDelegateForColumn(0, new EntityDelegate(m_ui->listv_objects));

	m_ui->listv_materials->setModel(&m_materialsModel);
	m_ui->listv_materials->setItemDelegateForColumn(0, new EntityDelegate(m_ui->listv_materials));

	connect(m_ui->btn_add,		&QPushButton::released,			this, &EntitiesWidget::onAddEntityBtnReleased);
	connect(m_ui->btn_delete,	&QPushButton::released,			this, &EntitiesWidget::onDeleteEntityBtnReleased);
	connect(m_ui->tabv_data,	&QTabWidget::currentChanged,	this, &EntitiesWidget::onCurrentTabChanged);

	{
		const QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
		connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onEntitySelected);
	}
	{
		const QItemSelectionModel* selectionModel = m_ui->listv_materials->selectionModel();
		connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onEntitySelected);
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setScene(jl::Scene* _scene)
{
	m_scene = _scene;

	if (m_scene)
	{
		const int objectsCount = m_scene->getObjectsCount();
		m_objectsModel.setRowCount(objectsCount);

		for (int i = 0; i < objectsCount; ++i)
		{
			const QModelIndex idx = m_objectsModel.index(i, 0);
			const QVariant data = QVariant::fromValue(ObjectUiWrapper{ &m_scene->getObject(i) });
			m_objectsModel.setData(idx, data);
		}
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setDefaultMaterial(jl::Material* _material)
{
	m_defaultMaterial = _material;
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setEntityActionHandler(IEntityActionHandler* _handler)
{
	m_actionHandler = _handler;
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onCurrentTabChanged(int _idx)
{
	const QWidget* currentTab = m_ui->tabv_data->widget(_idx);
	if (currentTab == m_ui->tab_objects)
	{
		const QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
		onEntitySelected(selectionModel->selection());
	}
	else if (currentTab == m_ui->tab_materials)
	{
		refreshMaterialsList();

		const QItemSelectionModel* selectionModel = m_ui->listv_materials->selectionModel();
		onEntitySelected(selectionModel->selection());
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onAddEntityBtnReleased()
{
	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while adding entity");
	if (m_ui->tab_objects->isVisible())
	{
		ASSERT(m_scene);
		if (m_scene)
		{
			addObject(computeObjectName());
		}
	}
	else if (m_ui->tab_materials->isVisible())
	{
		addMaterial(computeMaterialName());
	}

	if (m_actionHandler)
	{
		m_actionHandler->resetSelection();
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::addObject(const std::string& _name)
{
	auto object = std::make_unique<jl::Object>();
	object->setName(_name);

	QVariant value = QVariant::fromValue(ObjectUiWrapper{ object.get() });
	appendItemToModel(m_objectsModel, value);

	m_scene->addObject(std::move(object));
}

//-----------------------------------------------------------------------------

void EntitiesWidget::addMaterial(const std::string& _name)
{
	jl::Material& material = MaterialsManager::getInstance().createMaterial(_name);

	if (m_defaultMaterial)
	{
		material = *m_defaultMaterial;
	}

	QVariant value = QVariant::fromValue(MaterialUiWrapper{ &material });
	appendItemToModel(m_materialsModel, value);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::appendItemToModel(QAbstractItemModel& _model, const QVariant& _value)
{
	_model.insertRow(_model.rowCount());

	const QModelIndex idx = _model.index(_model.rowCount() - 1, 0);
	_model.setData(idx, _value);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onDeleteEntityBtnReleased()
{
	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while removing entity");
	if (m_ui->tab_objects->isVisible())
	{
		ASSERT(m_scene);
		if (m_scene)
		{
			auto deleteFun = std::bind(&EntitiesWidget::deleteObject, this, std::placeholders::_1);
			deleteEntities(*m_ui->listv_objects->selectionModel(), deleteFun);
		}
	}
	else if (m_ui->tab_materials->isVisible())
	{
		auto deleteFun = std::bind(&EntitiesWidget::deleteMaterial, this, std::placeholders::_1);
		deleteEntities(*m_ui->listv_materials->selectionModel(), deleteFun);
	}

	if (m_actionHandler)
	{
		m_actionHandler->resetSelection();
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::deleteObject(const QModelIndex& _idx)
{
	m_scene->eraseObject(_idx.row());
	m_objectsModel.removeRow(_idx.row());
}

//-----------------------------------------------------------------------------

void EntitiesWidget::deleteMaterial(const QModelIndex& _idx)
{
	const MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_idx.data());

	if (m_defaultMaterial != materialWrapper.value)
	{
		replaceMaterialInAllMeshes(materialWrapper.value, m_defaultMaterial);

		MaterialsManager::getInstance().deleteMaterial(*materialWrapper.value);
		m_materialsModel.removeRow(_idx.row());
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::deleteEntities(
	const QItemSelectionModel& _selectionModel,
	std::function<void(const QModelIndex&)>&& _deleteFun
)
{
	const QModelIndexList indexList = _selectionModel.selectedIndexes();

	ASSERT(std::is_sorted(indexList.begin(), indexList.end(), [](const QModelIndex& _lhs, const QModelIndex& _rhs)
	{
		return _lhs.row() < _rhs.row();
	}));

	std::for_each(indexList.rbegin(), indexList.rend(), [deleter = std::move(_deleteFun)](const QModelIndex& _idx)
	{
		deleter(_idx);
	});
}

//-----------------------------------------------------------------------------

void EntitiesWidget::replaceMaterialInAllMeshes(jl::Material* _old, jl::Material* _new)
{
	if (!m_scene)
	{
		return;
	}

	const int objectsCount = m_scene->getObjectsCount();
	for (int i = 0; i < objectsCount; ++i)
	{
		if (jl::Model* model = m_scene->getObject(i).getModel())
		{
			const size_t meshesCount = model->getMeshesCount();
			for (size_t i = 0; i < meshesCount; i++)
			{
				jl::Mesh& mesh = model->getMesh(i);

				const jl::Material* meshMaterial = mesh.getMaterial();
				if (meshMaterial == _old)
				{
					mesh.setMaterial(_new);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::refreshMaterialsList()
{
	MaterialsManager& mgr = MaterialsManager::getInstance();
	m_materialsModel.setRowCount(mgr.getMaterialsCount());

	int counter = 0;
	mgr.forEachMaterial([&counter, this](jl::Material& _material)
	{
		QVariant data = QVariant::fromValue(MaterialUiWrapper{ &_material });
		m_materialsModel.setData(m_materialsModel.index(counter++, 0), data);
	});
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onEntitySelected(const QItemSelection& _selection)
{
	ASSERT(m_actionHandler);
	if (!m_actionHandler)
	{
		return;
	}

	const QModelIndexList indexList = _selection.indexes();
	if (indexList.size() == 1)
	{
		const QModelIndex& idx = indexList.back();

		ASSERT(idx.data().canConvert<ObjectUiWrapper>() || idx.data().canConvert<MaterialUiWrapper>());
		if (idx.data().canConvert<ObjectUiWrapper>())
		{
			const ObjectUiWrapper objWrapper = qvariant_cast<ObjectUiWrapper>(idx.data());
			m_actionHandler->objectSelected(*objWrapper.value);
		}
		else if (idx.data().canConvert<MaterialUiWrapper>())
		{
			MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(idx.data());
			m_actionHandler->materialSelected(*materialWrapper.value);
		}
	}
	else
	{
		m_actionHandler->resetSelection();
	}
}

//-----------------------------------------------------------------------------

std::string EntitiesWidget::computeObjectName() const
{
	return computeEntityName(k_defaultObjectName, [this](const std::string& _name)
	{
		return m_scene->findObjectByName(_name) != nullptr;
	});
}

//-----------------------------------------------------------------------------

std::string EntitiesWidget::computeMaterialName() const
{
	return computeEntityName(k_defaultMaterialName, [](const std::string& _name)
	{
		return MaterialsManager::getInstance().findMaterial(_name) != nullptr;
	});
}

//-----------------------------------------------------------------------------

std::string EntitiesWidget::computeEntityName(
	std::string_view _base,
	std::function<bool(const std::string&)>&& _entityExistCheckFun
)
{
	std::string result = _base.data();
	int counter = 0;

	while (_entityExistCheckFun(result))
	{
		fmt::memory_buffer buf;
		format_to(buf, "{:03d}", ++counter);

		const size_t offset = result.length() - 3;
		result.replace(offset, 3, buf.data(), 3); // last param need due to MSVC bug
	}

	return result;
}

//-----------------------------------------------------------------------------
