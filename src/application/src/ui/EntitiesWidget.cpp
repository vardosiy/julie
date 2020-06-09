#include "ui/EntitiesWidget.hpp"
#include "ui_EntitiesWidget.h"

#include "data/SceneWrapper.hpp"

#include "renderer/managers/MaterialsManager.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Model.hpp"
#include "renderer/Material.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

EntitiesWidget::EntitiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_objectsListModel(this)
	, m_materialsListModel(this)
{
	m_ui = std::make_unique<Ui::EntitiesWidget>();
	m_ui->setupUi(this);

	m_ui->listv_objects->setModel(&m_objectsListModel);
	m_ui->listv_materials->setModel(&m_materialsListModel);

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

void EntitiesWidget::setScene(SceneWrapper* _sceneWrapper)
{
	m_sceneWrapper = _sceneWrapper;

	if (m_sceneWrapper)
	{
		m_sceneWrapper->forEachObject([this](ObjectWrapper& _objWrapper)
		{
			m_objectsNamesList.append(_objWrapper.getName().c_str());
		});
		m_objectsListModel.setStringList(m_objectsNamesList);

		refreshMaterialsList();
	}
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

void EntitiesWidget::refreshMaterialsList()
{
	m_materialsNamesList.clear();

	MaterialsManager::getInstance().forEachMaterial([this](const std::string& _name, const jl::Material&)
	{
		m_materialsNamesList.append(_name.c_str());
	});
	m_materialsListModel.setStringList(m_materialsNamesList);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onAddEntityBtnReleased()
{
	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while adding entity");
	if (m_ui->tab_objects->isVisible())
	{
		ASSERT(m_sceneWrapper);
		if (m_sceneWrapper)
		{
			addObject(computeObjectName());
		}
	}
	else if (m_ui->tab_materials->isVisible())
	{
		addMaterial(computeMaterialName());
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::addObject(const std::string& _name)
{
	auto object = std::make_unique<jl::Object>(_name);

	m_objectsNamesList.append(_name.c_str());
	m_objectsListModel.setStringList(m_objectsNamesList);

	m_sceneWrapper->addObject(std::move(object));
}

//-----------------------------------------------------------------------------

void EntitiesWidget::addMaterial(const std::string& _name)
{
	jl::Material& material = MaterialsManager::getInstance().createMaterial(_name);

	m_materialsNamesList.append(_name.c_str());
	m_materialsListModel.setStringList(m_materialsNamesList);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onDeleteEntityBtnReleased()
{
	const QItemSelectionModel* selectionModel = nullptr;
	std::function<void(const QString&)> deleteFun;

	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while removing entity");
	if (m_ui->tab_objects->isVisible())
	{
		ASSERT(m_sceneWrapper);
		if (m_sceneWrapper)
		{
			selectionModel = m_ui->listv_objects->selectionModel();
			deleteFun = std::bind(&EntitiesWidget::deleteObject, this, std::placeholders::_1);
		}
	}
	else if (m_ui->tab_materials->isVisible())
	{
		selectionModel = m_ui->listv_materials->selectionModel();
		deleteFun = std::bind(&EntitiesWidget::deleteMaterial, this, std::placeholders::_1);
	}

	if (selectionModel && deleteFun)
	{
		const QModelIndexList indexList = selectionModel->selectedIndexes();

		if (!indexList.empty())
		{
			std::vector<QString> itemsToRemove;
			itemsToRemove.reserve(indexList.size());

			for (const auto& index : indexList)
			{
				itemsToRemove.emplace_back(index.data().toString());
			}
			for (const QString& itemName : itemsToRemove)
			{
				deleteFun(itemName);
			}
		}

		if (m_actionHandler)
		{
			m_actionHandler->resetSelection();
		}
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::deleteObject(const QString& _name)
{
	const std::string objName = _name.toStdString();
	m_sceneWrapper->removeObject(objName);

	auto itNames = std::find(m_objectsNamesList.begin(), m_objectsNamesList.end(), _name);
	if (itNames != m_objectsNamesList.end())
	{
		m_objectsNamesList.erase(itNames);
		m_objectsListModel.setStringList(m_objectsNamesList);
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::deleteMaterial(const QString& _name)
{
	MaterialsManager& materialsMgr = MaterialsManager::getInstance();
	const std::string materialName = _name.toStdString();

	if (jl::Material* material = materialsMgr.findMaterial(materialName))
	{
		replaceMaterialInAllMeshes(material, &materialsMgr.getDefaultMaterial());

		materialsMgr.deleteMaterial(materialName);
		m_materialsNamesList.removeOne(_name);
		m_materialsListModel.setStringList(m_materialsNamesList);
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::replaceMaterialInAllMeshes(const jl::Material* _old, const jl::Material* _new)
{
	if (!m_sceneWrapper)
	{
		return;
	}

	m_sceneWrapper->forEachObject([_old, _new](ObjectWrapper& _objWrapper)
	{
		if (jl::Model* model = _objWrapper.getModel())
		{
			const jl::u32 meshesCount = model->getMeshesCount();
			for (jl::u32 i = 0; i < meshesCount; i++)
			{
				jl::Mesh& mesh = model->getMesh(i);

				const jl::Material* meshMaterial = mesh.getMaterial();
				if (meshMaterial == _old)
				{
					mesh.setMaterial(_new);
				}
			}
		}
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
		const std::string entityName = indexList.back().data().toString().toStdString();

		ASSERT(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible());
		if (m_ui->tab_objects->isVisible())
		{
			ASSERT(m_sceneWrapper);
			if (m_sceneWrapper)
			{
				if (ObjectWrapper* objWrapper = m_sceneWrapper->findObject(entityName))
				{
					m_actionHandler->objectSelected(*objWrapper);
				}
			}
		}
		else if (m_ui->tab_materials->isVisible())
		{
			if (jl::Material* material = MaterialsManager::getInstance().findMaterial(entityName))
			{
				m_actionHandler->materialSelected(*material);
			}
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
		return m_sceneWrapper->findObject(_name) != nullptr;
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
