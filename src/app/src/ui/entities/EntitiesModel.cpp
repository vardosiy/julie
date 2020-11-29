//#include "ui/entities/EntitiesModel.hpp"
//
////-----------------------------------------------------------------------------
//
//BrowserModel::BrowserModel(QObject* parent)
//	: QAbstractItemModel(parent)
//	, Messenger()
//{
//	m_sources = 0xFFFFFFF;
//	m_type = k_treeTypeNormal;
//
//	m_rootItem = 0;
//	m_rootNode = 0;
//
//	Messenger::ListenTo(Project::GetInstance());
//}
//
////-----------------------------------------------------------------------------
//
//BrowserModel::~BrowserModel()
//{
//	WriteNodeFlags();
//
//	delete m_rootItem;
//	m_rootItem = 0;
//	m_rootNode = 0;
//}
//
////-----------------------------------------------------------------------------
//
//int BrowserModel::columnCount(const QModelIndex& parent) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	return m_rootItem ? 1 : 0;
//}
//
////-----------------------------------------------------------------------------
//
//QVariant BrowserModel::data(const QModelIndex& index, int role) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (!index.isValid())
//	{
//		if (role == Qt::EditRole)
//		{
//			return QString();
//		}
//		return QVariant();
//	}
//
//	TreeItem* item = (TreeItem*)index.internalPointer();
//
//	if (role == Qt::DecorationRole)
//	{
//		if (index.column() == 0)
//		{
//			return item->GetIcon();
//		}
//	}
//	else if (role == Qt::DisplayRole)
//	{
//		return item->GetData(index.column());
//	}
//	else if (role == Qt::EditRole)
//	{
//		return item->GetData(-1);
//	}
//	else if (role == Qt::TextColorRole)
//	{
//		QColor color(Qt::black);
//		if (item->GetParent()->GetType() == TreeItem::k_typeGroup)
//		{
//			color = Qt::blue;
//		}
//
//		bool visible = item->GetClaraNode() ? item->GetClaraNode()->IsVisible(false) : true;
//		bool imVisible = !visible ? item->GetClaraNode()->IsVisible(true) : true;
//		if (!visible)
//		{
//			QColor c = imVisible ? Qt::gray : Qt::lightGray;
//			color.setRgbF((color.redF() + c.redF()) * 0.5f, (color.greenF() + c.greenF()) * 0.5f, (color.blueF() + c.blueF()) * 0.5f);
//		}
//
//		return color;
//	}
//
//	return QVariant();
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::setData(const QModelIndex& index, const QVariant& value, int role /* = Qt::EditRole*/)
//{
//	return false;
//}
//
////-----------------------------------------------------------------------------
//
//Qt::ItemFlags BrowserModel::flags(const QModelIndex& index) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (!index.isValid())
//	{
//		return 0;
//	}
//
//	TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
//
//	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//	if (item->GetClaraNode() && item->GetClaraNode()->IsGloballyLocked())
//	{
//		return flags;
//	}
//
//	if (item->GetType() == TreeItem::k_typeClaraFile)
//	{
//		ClaraFile* cf = (ClaraFile*)item->GetClaraNode();
//		if (cf->IsOpen())
//		{
//			flags |= Qt::ItemIsDropEnabled;
//		}
//	}
//	else if (item->GetType() == TreeItem::k_typeEntity)
//	{
//		//entity references are not draggable, nor editable
//		if (item->GetParent()->GetType() != TreeItem::k_typeGroup)
//		{
//			flags |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled;
//		}
//	}
//	else if (item->GetType() == TreeItem::k_typeMovie)
//	{
//		flags |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled;
//	}
//	else if (item->GetType() == TreeItem::k_typeFolder)
//	{
//		flags |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
//
//		//the root folder cannot be moved or renamed
//		if (CNCast<Folder>(item->GetClaraNode())->IsRoot())
//		{
//			flags &= ~(Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
//		}
//	}
//	else if (item->GetType() == TreeItem::k_typeGroup)
//	{
//		flags |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled
//			| Qt::ItemIsDropEnabled;
//	}
//	else if (item->GetType() == TreeItem::k_typeMultiLayer)
//	{
//		flags |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled;
//	}
//
//	if (GetType() == k_treeTypeScripting)
//	{
//		flags &= ~(Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDragEnabled);
//	}
//
//	return flags;
//}
//
////-----------------------------------------------------------------------------
//
//Qt::DropActions BrowserModel::supportedDropActions() const
//{
//	return Qt::MoveAction | Qt::CopyAction;
//}
//
////-----------------------------------------------------------------------------
//
//QMimeData* BrowserModel::mimeData(const QModelIndexList& indexes) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (indexes.count() <= 0)
//	{
//		return 0;
//	}
//
//	QStringList types = mimeTypes();
//	if (types.isEmpty())
//	{
//		return 0;
//	}
//
//	QString format = types.at(0);
//	QByteArray encoded;
//	QDataStream stream(&encoded, QIODevice::WriteOnly);
//
//	TreeItem* commonParent = 0; //to check if all are under the same parent
//	stream << indexes.count();
//	QModelIndexList::ConstIterator it = indexes.begin();
//	for (; it != indexes.end(); ++it)
//	{
//		TreeItem* item = GetTreeItem(*it);
//		TreeItem* p = GetTreeItem(parent(*it));
//		if (!commonParent)
//		{
//			commonParent = p;
//		}
//		else if (commonParent != p)
//		{
//			return 0;
//		}
//
//		stream << item->GetType() << item->GetId();
//	}
//
//	QMimeData* data = new QMimeData();
//	data->setData(format, encoded);
//	return data;
//}
//
////-----------------------------------------------------------------------------
//
//QStringList BrowserModel::mimeTypes() const
//{
//	QStringList types;
//
//	if (m_type == k_treeTypeNormal)
//	{
//		types << "application/x-claranodelist";
//		types << "application/x-claratemplateid";
//		types << "application/x-claramovie";
//		types << "application/x-clarapath";
//		types << "application/x-clarafolder";
//		types << "application/x-claragroup";
//		types << "application/x-claramultilayer";
//
//		types << QAbstractItemModel::mimeTypes();
//	}
//
//	return types;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (m_type == k_treeTypeScripting)
//	{
//		return false;
//	}
//
//	// check if the action is supported
//	if (!data)
//	{
//		return false;
//	}
//
//	// check if the format is supported
//	QStringList types = mimeTypes();
//	if (types.isEmpty())
//	{
//		return false;
//	}
//
//	if (row > rowCount(parent))
//	{
//		row = rowCount(parent);
//	}
//	if (row == -1)
//	{
//		row = rowCount(parent);
//	}
//	if (column == -1)
//	{
//		column = 0;
//	}
//
//	if (data->hasFormat("application/x-claranodelist"))
//	{
//		return MoveClaraNodes(data, action, row, column, parent);
//	}
//	else if (action == Qt::CopyAction && data->hasFormat("application/x-claratemplateid"))
//	{
//		return CreateEntity(data, action, row, column, parent);
//	}
//	else if (action == Qt::CopyAction && data->hasFormat("application/x-claramovie"))
//	{
//		return CreateMovie(data, action, row, column, parent);
//	}
//	else if (action == Qt::CopyAction && data->hasFormat("application/x-clarafolder"))
//	{
//		return CreateFolder(data, action, row, column, parent);
//	}
//	else if (action == Qt::CopyAction && data->hasFormat("application/x-claragroup"))
//	{
//		return CreateGroup(data, action, row, column, parent);
//	}
//	else if (action == Qt::CopyAction && data->hasFormat("application/x-claramultilayer"))
//	{
//		return CreateMultiLayer(data, action, row, column, parent);
//	}
//
//	return false;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::MoveClaraNodes(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	TreeItem* dst = GetTreeItem(parent);
//	if (dst->GetType() != TreeItem::k_typeClaraFile &&
//		dst->GetType() != TreeItem::k_typeFolder &&
//		dst->GetType() != TreeItem::k_typeGroup &&
//		dst->GetType() != TreeItem::k_typeEntity &&
//		dst->GetType() != TreeItem::k_typeMovie &&
//		dst->GetType() != TreeItem::k_typeMultiLayer)
//	{
//		return false;
//	}
//
//	ClaraNode* dstFolder = 0;
//	ClaraFile* dstClaraFile = 0;
//	if (dst->GetType() == TreeItem::k_typeClaraFile)
//	{
//		dstClaraFile = CNCast<ClaraFile>(dst->GetClaraNode());
//		dstFolder = dstClaraFile->GetRoot();
//	}
//	else
//	{
//		dstFolder = dst->GetClaraNode();
//		dstClaraFile = dstFolder->GetClaraFile();
//	}
//
//	//ca only copy to the active clara file, or a library
//	if (Project::GetInstance()->GetActiveClaraFile() != dstClaraFile && !dstClaraFile->IsLibrary())
//	{
//		return false;
//	}
//
//	if (!dstClaraFile)
//	{
//		return false;
//	}
//
//	// decode and insert
//	QByteArray encoded = data->data("application/x-claranodelist");
//	QDataStream stream(&encoded, QIODevice::ReadOnly);
//
//	//decode data
//	u32 count;
//	stream >> count;
//
//	if (count == 0)
//	{
//		return false;
//	}
//
//	PArray<u32> nodes;
//	nodes.reserve(count);
//
//	for (u32 i = 0; i < count; i++)
//	{
//		int type;
//		u32 id;
//		stream >> type >> id;
//
//		if (type == TreeItem::k_typeEntity ||
//			type == TreeItem::k_typeFolder ||
//			type == TreeItem::k_typeGroup ||
//			type == TreeItem::k_typeMovie ||
//			type == TreeItem::k_typeMultiLayer
//			)
//		{
//			nodes.push_back(id);
//		}
//	}
//
//	ClaraFile* srcClaraFile = 0;
//	if (nodes.size() > 0)
//	{
//		ClaraNode* node = ClaraNode::FindById(nodes[0]);
//		srcClaraFile = node->GetClaraFile();
//	}
//
//	if (action == Qt::CopyAction)
//	{
//		//copying is not permitted in groups
//		if (typeid(*dstFolder) != typeid(Group*))
//		{
//			CommandMgr::GetInstance()->Do(new CopyClaraNodesCmd(dstFolder, nodes));
//		}
//	}
//	else if (action == Qt::MoveAction)
//	{
//		CommandMgr::GetInstance()->Do(new MoveClaraNodesCmd(dstFolder, nodes));
//	}
//
//	// 	if (srcClaraFile->GetId() != dstClaraFile->GetId())
//	// 	{
//	// 		//copying is not permitted in groups
//	// 		if (typeid(*dstFolder) != typeid(Group*))
//	// 			CommandMgr::GetInstance()->Do(new CopyClaraNodesCmd(dstFolder, nodes));
//	// 	}
//	// 	else
//	// 		CommandMgr::GetInstance()->Do(new MoveClaraNodesCmd(dstFolder, nodes));
//
//	m_needsRefresh = true;
//
//	return true;
//}
//
////-----------------------------------------------------------------------------
//
//Folder* BrowserModel::GetDestinationFolder(TreeItem* dst)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (!dst)
//	{
//		return 0;
//	}
//
//	if (dst->GetType() != TreeItem::k_typeClaraFile &&
//		dst->GetType() != TreeItem::k_typeFolder &&
//		dst->GetType() != TreeItem::k_typeGroup &&
//		dst->GetType() != TreeItem::k_typeEntity &&
//		dst->GetType() != TreeItem::k_typeMovie &&
//		dst->GetType() != TreeItem::k_typeMultiLayer
//		)
//	{
//		return 0;
//	}
//
//	ClaraNode* dstFolder = 0;
//	if (dst->GetType() == TreeItem::k_typeClaraFile)
//	{
//		dstFolder = ((ClaraFile*)dst->GetClaraNode())->GetRoot();
//	}
//	if (dst->GetType() == TreeItem::k_typeFolder)
//	{
//		dstFolder = dst->GetClaraNode();
//	}
//	if (dst->GetType() == TreeItem::k_typeGroup)
//	{
//		dstFolder = dst->GetClaraNode();
//	}
//	if (dst->GetType() == TreeItem::k_typeEntity)
//	{
//		dstFolder = dst->GetClaraNode()->GetContainer();
//	}
//	if (dst->GetType() == TreeItem::k_typeMovie)
//	{
//		dstFolder = dst->GetClaraNode()->GetContainer();
//	}
//	if (dst->GetType() == TreeItem::k_typeMultiLayer)
//	{
//		dstFolder = dst->GetClaraNode()->GetContainer();
//	}
//
//	if (!dstFolder || !dstFolder->GetClaraFile())
//	{
//		return 0;
//	}
//
//	return (Folder*)dstFolder;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::CreateEntity(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	Folder* dstFolder = GetDestinationFolder(GetTreeItem(parent));
//	if (!dstFolder)
//	{
//		return false;
//	}
//
//	// decode and insert
//	QByteArray encoded = data->data("application/x-claratemplateid");
//	QDataStream stream(&encoded, QIODevice::ReadOnly);
//
//	//decode data
//	u32 tmplId;
//	stream >> tmplId;
//	if (!tmplId)
//	{
//		return false;
//	}
//
//	Template* tmpl = Project::GetInstance()->FindTemplateById(tmplId);
//	if (!tmpl)
//	{
//		return false;
//	}
//
//	CommandMgr::GetInstance()->Do(new CreateEntityCmd(dstFolder, tmplId, GetGLWidget(this)->GetFocusPoint()));
//
//	BrowserWnd* browser = BrowserWnd::GetMain();
//	if (browser)
//	{
//		browser->SelectClaraNode(CreateEntityCmd::GetLastCreatedNodeId(), true);
//	}
//
//	m_needsRefresh = true;
//
//	return true;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::CreateMovie(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	Folder* dstFolder = GetDestinationFolder(GetTreeItem(parent));
//	if (!dstFolder)
//	{
//		return false;
//	}
//
//	CommandMgr::GetInstance()->Do(new CreateMovieCmd(dstFolder));
//
//	m_needsRefresh = true;
//
//	return true;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::CreateFolder(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	Folder* dstFolder = GetDestinationFolder(GetTreeItem(parent));
//	if (!dstFolder)
//	{
//		return false;
//	}
//
//	CommandMgr::GetInstance()->Do(new CreateFolderCmd(dstFolder));
//
//	m_needsRefresh = true;
//
//	return true;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::CreateGroup(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	Folder* dstFolder = GetDestinationFolder(GetTreeItem(parent));
//	if (!dstFolder)
//	{
//		return false;
//	}
//
//	CommandMgr::GetInstance()->Do(new CreateGroupCmd(dstFolder));
//
//	m_needsRefresh = true;
//
//	return true;
//}
//
////-----------------------------------------------------------------------------
//
//bool BrowserModel::CreateMultiLayer(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	Folder* dstFolder = GetDestinationFolder(GetTreeItem(parent));
//	if (!dstFolder)
//	{
//		return false;
//	}
//
//	CommandMgr::GetInstance()->Do(new CreateMultiLayerCmd(dstFolder));
//
//	m_needsRefresh = true;
//
//	return true;
//}
//
////-----------------------------------------------------------------------------
//
//QVariant BrowserModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//	{
//		return m_rootItem->GetData(section);
//	}
//
//	return QVariant();
//}
//
////-----------------------------------------------------------------------------
//
//QModelIndex BrowserModel::index(int row, int column, const QModelIndex& parent) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	// 	if (!hasIndex(row, column, parent))
//	// 		return QModelIndex();
//
//	TreeItem* parentItem = _GetTreeItem(parent);
//	if (!parentItem || row >= (int)parentItem->GetChildCount())
//	{
//		return QModelIndex();
//	}
//
//	TreeItem* childItem = parentItem->GetChild(row);
//	if (childItem)
//	{
//		return createIndex(row, column, childItem);
//	}
//	else
//	{
//		return QModelIndex();
//	}
//}
//
////-----------------------------------------------------------------------------
//
//QModelIndex BrowserModel::parent(const QModelIndex& index) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (!index.isValid())
//	{
//		return QModelIndex();
//	}
//
//	TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
//	TreeItem* parentItem = childItem->GetParent();
//
//	if (parentItem == m_rootItem)
//	{
//		return QModelIndex();
//	}
//
//	return createIndex(parentItem->GetRow(), 0, parentItem);
//}
//
////-----------------------------------------------------------------------------
//
//int BrowserModel::rowCount(const QModelIndex& parent) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (parent.column() > 0)
//	{
//		return 0;
//	}
//
//	TreeItem* parentItem = _GetTreeItem(parent);
//	return parentItem ? parentItem->GetChildCount() : 0;
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::expand(const QModelIndex& index)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	TreeItem* item = _GetTreeItem(index);
//	if (item)
//	{
//		m_expandedItems[item->GetData(-1).toString()] = true;
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::collapse(const QModelIndex& index)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	TreeItem* item = _GetTreeItem(index);
//	if (item)
//	{
//		m_expandedItems[item->GetData(-1).toString()] = false;
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::BuildModel(QTreeView* tree)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//
//	m_needsRefresh = false;
//
//	Reset();
//
//	int bc = math::getOnBitsCount(m_sources);
//	PASSERT2(bc > 0, "You have to specify a source.");
//
//	m_rootItem = new TreeItem(this, "", "");
//
//	TreeItem* cfRoot = m_rootItem;
//	TreeItem* libRoot = m_rootItem;
//	TreeItem* resRoot = m_rootItem;
//
//	if (bc > 1)
//	{
//		if (HasSource(k_sourceClaraFiles))
//		{
//			cfRoot = new TreeItem(this, "Clara Files", "clarafile-opened", m_rootItem);
//			m_rootItem->AddChild(cfRoot);
//		}
//		if (HasSource(k_sourceLibraries))
//		{
//			libRoot = new TreeItem(this, "Libraries", "library", m_rootItem);
//			m_rootItem->AddChild(libRoot);
//		}
//		if (HasSource(k_sourceResources))
//		{
//			resRoot = new TreeItem(this, "Resources", "resource", m_rootItem);
//			m_rootItem->AddChild(resRoot);
//		}
//	}
//
//	if (m_rootNode)
//	{
//		ClaraFile* cf = CNCast<ClaraFile>(m_rootNode);
//		if (cf)
//		{
//			if (cf->IsLibrary() && HasSource(k_sourceLibraries))
//			{
//				libRoot->AddChild(new ClaraFileTreeItem(this, libRoot, cf));
//			}
//			else if (!cf->IsLibrary() && HasSource(k_sourceClaraFiles))
//			{
//				cfRoot->AddChild(new ClaraFileTreeItem(this, cfRoot, cf));
//			}
//		}
//	}
//	else
//	{
//		Project* prj = Project::GetInstance();
//		for (u32 cIdx = 0; cIdx < prj->GetClaraFileCount(); cIdx++)
//		{
//			ClaraFile* cf = prj->GetClaraFile(cIdx);
//			if (cf->IsLibrary() && HasSource(k_sourceLibraries) && !cf->IsInternal())
//			{
//				libRoot->AddChild(new ClaraFileTreeItem(this, libRoot, cf));
//			}
//			else if (!cf->IsLibrary() && HasSource(k_sourceClaraFiles) && !cf->IsInternal())
//			{
//				cfRoot->AddChild(new ClaraFileTreeItem(this, cfRoot, cf));
//			}
//		}
//	}
//
//	// async call, restore flags when the proxyModel is ready
//	metaObject()->invokeMethod(this, "ReadNodeFlags", Qt::QueuedConnection,
//		Q_ARG(QTreeView*, tree));
//
//	emit layoutChanged();
//
//
//	if (tree)
//	{
//		//ms to force an update of the geometry 
//		QRect r = tree->rect();
//		QModelIndex tl = tree->indexAt(r.topLeft());
//		QModelIndex br = tree->indexAt(r.bottomRight());
//		emit dataChanged(tl, br);
//	}
//
//	//restore selection and 
//	//scroll 
//
//	ListenTo(m_rootItem);
//
//	emit tryRestoreSelectionAndScroll();
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::ListenTo(TreeItem* item)
//{
//	if (!item)
//	{
//		return;
//	}
//
//	u64 typeMask = ClaraNode::k_msgType | Visual::k_msgType | Value::k_msgType;
//	u64 messageMask = msg::DESTROYED | msg::DELETED | msg::HIERARCHY_CHANGED | msg::CLARAFILE_CHANGED |
//		msg::NAME_CHANGED | msg::VISIBILITY_CHANGED | msg::ERRORS_CHANGED | msg::VALUE_CHANGED;
//
//	ClaraNode* node = item->GetClaraNode();
//	Messenger::ListenTo(node, typeMask, messageMask);
//
//	for (u32 i = 0, sz = item->GetChildCount(); i < sz; i++)
//	{
//		ListenTo(item->GetChild(i));
//	}
//}
//
////-----------------------------------------------------------------------------
//
//// void BrowserModel::RestoreCollapseState(QTreeView* tree, const QModelIndex& parent)
//// {
//// 	int count = rowCount(parent);
//// 	if (count <= 0)
//// 		return;
//// 
//// 	QString str = (QString&)data(parent, Qt::EditRole);
//// 	ExpandedItemsMap::iterator it = m_expandedItems.find(str);
//// 	if (it != m_expandedItems.end())
//// 	{
//// 		tree->setExpanded(parent, it->second);
//// 	}
//// 
//// 	for (int r = 0; r < count; ++r)
//// 	{
//// 		QModelIndex node = index(r, 0, parent);
//// 		RestoreCollapseState(tree, node);
//// 	}
//// }
//
//TreeItem* BrowserModel::_GetTreeItem(const QModelIndex& index) const
//{
//	if (!index.isValid())
//	{
//		return m_rootItem;
//	}
//	else
//	{
//		return static_cast<TreeItem*>(index.internalPointer());
//	}
//}
//
////-----------------------------------------------------------------------------
//
//TreeItem* BrowserModel::GetTreeItem(const QModelIndex& index) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	return _GetTreeItem(index);
//}
//
////-----------------------------------------------------------------------------
//
//QModelIndex BrowserModel::FindModelIndex(u32 id, const QModelIndex& parent, bool searchHiddenChildren) const
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	TreeItem* parentItem = _GetTreeItem(parent);
//	if (!m_rootItem || !parentItem)
//	{
//		return QModelIndex();
//	}
//	return _FindModelIndex(id, parent, parentItem, searchHiddenChildren);
//}
//
////-----------------------------------------------------------------------------
//
//QModelIndex BrowserModel::_FindModelIndex(u32 id, const QModelIndex& parent, TreeItem* parentItem, bool searchHiddenChildren) const
//{
//	//don't search in groups
//	if (parentItem->GetType() == TreeItem::k_typeGroup)
//	{
//		return QModelIndex();
//	}
//
//	for (u32 r = 0, sz = parentItem->GetChildCount(); r < sz; ++r)
//	{
//		TreeItem* childItem = parentItem->GetChild(r);
//		if (childItem->GetId() == id)
//		{
//			QModelIndex node = index(r, 0, parent);
//			return node;
//		}
//
//		if (childItem->GetChildCount() > 0)
//		{
//			QModelIndex node = index(r, 0, parent);
//
//			QModelIndex res = _FindModelIndex(id, node, childItem, searchHiddenChildren);
//			if (res.isValid())
//			{
//				return res;
//			}
//
//			if (searchHiddenChildren && childItem->HasChildWithId(id))
//			{
//				return node;
//			}
//		}
//	}
//
//	return QModelIndex();
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::Reset()
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//
//	WriteNodeFlags();
//
//	trySaveSelectionAndScroll();
//	//notify view that this will be destroyd !!!!
//
//	//ptodo save selection and scroll 
//	//#if QT_VERSION >= 0x050000
//	//	resetInternalData();
//	//#else
//	//reset();
//	//#endif
//
//	beginResetModel();
//	delete m_rootItem;
//	m_rootItem = 0;
//	endResetModel();
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::OnMessageReceived(const clara::msg::Message& msg)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//
//	Messenger::OnMessageReceived(msg);
//
//	if (msg.IsFrom<Project>())
//	{
//		if (m_rootItem && (msg.Is(msg::PROJECT_CLOSED) || msg.Is(msg::PROJECT_OPENED)))
//		{
//			Reset();
//		}
//
//		if (m_rootItem && msg.Is(msg::PROJECT_SAVED))
//		{
//			WriteNodeFlags();
//		}
//	}
//
//	if (msg.IsFrom<ClaraNode>() && (msg.Is(msg::DESTROYED) || msg.Is(msg::DELETED)))
//	{
//		if (m_rootItem)
//		{
//			u32 id(msg.GetId());
//			if (id)
//			{
//				QModelIndex item = FindModelIndex(id);
//				if (item.isValid())
//				{
//					Reset();
//				}
//			}
//		}
//	}
//
//	if (msg.IsFrom<ClaraNode>())
//	{
//		if (m_rootItem)
//		{
//			u32 id(msg.GetId());
//			if (id)
//			{
//				if (msg.Is(msg::UNDELETED) |
//					msg.Is(msg::HIERARCHY_CHANGED) |
//					msg.Is(msg::CLARAFILE_CHANGED) |
//					msg.Is(msg::NAME_CHANGED))
//				{
//					Reset();
//				}
//				if (msg.Is(msg::VISIBILITY_CHANGED))
//				{
//					QModelIndex item = FindModelIndex(id);
//					if (item.isValid())
//					{
//						emit dataChanged(item, item);
//					}
//				}
//			}
//		}
//	}
//
//	if (msg.IsFrom<ClaraNode>() || msg.IsFrom<Visual>())
//	{
//		if (msg.Is(msg::ERRORS_CHANGED))
//		{
//			if (m_rootItem)
//			{
//				u32 id(msg.GetId());
//				if (id)
//				{
//					QModelIndex item = FindModelIndex(id);
//					if (!item.isValid())
//					{
//						//this id in not in the tree. Check all it's containers until one is found
//						while (id && !item.isValid())
//						{
//							ClaraNode* node = ClaraNode::FindById(id);
//							if (node && node->GetContainer())
//							{
//								id = node->GetContainer()->GetId();
//								item = FindModelIndex(id);
//							}
//							else
//							{
//								break;
//							}
//						}
//					}
//					if (item.isValid())
//					{
//						emit dataChanged(item, item);
//						QModelIndex parent = item.parent();
//						while (parent.isValid())
//						{
//							emit dataChanged(parent, parent);
//							parent = parent.parent();
//						}
//					}
//				}
//			}
//		}
//	}
//
//	if (GetType() == k_treeTypeScripting)
//	{
//		if (msg.IsFrom<Value>())
//		{
//			if (msg.Is(msg::VALUE_CHANGED))
//			{
//				if (m_rootItem)
//				{
//					u32 id(msg.GetId());
//					if (id)
//					{
//						QModelIndex item = FindModelIndex(id);
//						if (item.isValid())
//						{
//							emit dataChanged(item, item);
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::WriteNodeFlags()
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//
//	if (!m_rootItem)
//	{
//		return;
//	}
//
//	//generate mangled name for the file
//	String fileName;
//	if (HasSource(k_sourceClaraFiles))
//	{
//		for (u32 i = 0; i < Project::GetInstance()->GetClaraFileCount(); i++)
//		{
//			ClaraFile* cf = Project::GetInstance()->GetClaraFile(i);
//			if (cf && cf->IsOpen() && !cf->IsLibrary())
//			{
//				fileName += cf->GetName();
//			}
//		}
//	}
//	if (HasSource(k_sourceLibraries))
//	{
//		fileName += "Libraries";
//	}
//
//	if (fileName.empty())
//	{
//		return;
//	}
//
//	if (Project::GetInstance()->GetProjectPath().empty())
//	{
//		return;
//	}
//
//	fileName = Project::GetInstance()->GetProjectPath() + "/" + fileName + ".els";
//
//	//generate ELS filename
//
//
//	QJsonArray rootArray;
//	QJsonObject root;
//	QFile f(fileName.c_str());
//	if (!f.open(QIODevice::WriteOnly))
//	{
//		PDBG("WARNING: cannot write editor-level-settings file");
//		return;
//	}
//
//	std::vector<TreeItem*> parents;
//	parents.reserve(10000);
//	parents.push_back(m_rootItem);
//	for (u32 i = 0; i < parents.size(); i++)
//	{
//		TreeItem* item = parents[i];
//		ClaraNode* node = item->GetClaraNode();
//		bool visible = node ? node->IsVisible(true) : true;
//
//		ExpandedItemsMap::iterator it = m_expandedItems.find(item->GetData(-1).toString());
//		bool expanded = (it != m_expandedItems.end()) ? it->second : false;
//
//		if (!visible || expanded)
//		{
//			String path = node->GetPath().GetAsString();
//			QJsonObject o;
//			o.insert("visible", visible);
//			o.insert("expanded", expanded);
//			root.insert(path.c_str(), o);
//		}
//
//		for (u32 c = 0; c < item->GetChildCount(); c++)
//		{
//			parents.push_back(item->GetChild(c));
//		}
//	}
//
//	if (!HasSource(k_sourceLibraries))
//	{
//		// save the current camera transform
//		GLWidget* w = GetGLWidget(this);
//		if (w != 0 && w->GetCamera() != 0)
//		{
//			jet::scene::Camera* cam = w->GetCamera();
//			math::vec3f p = cam->GetPosition();
//			math::quatf rot = cam->GetRotation();
//
//			QJsonObject o;
//
//			o.insert("pos_x", p.x);
//			o.insert("pos_y", p.y);
//			o.insert("pos_z", p.z);
//
//			o.insert("rot_x", rot.x);
//			o.insert("rot_y", rot.y);
//			o.insert("rot_z", rot.z);
//			o.insert("rot_w", rot.w);
//
//			root.insert("__camera__", o);
//		}
//	}
//
//	if (!root.isEmpty())
//	{
//		QJsonDocument doc(root);
//		QByteArray data;
//		data = doc.toBinaryData();
//		f.write(data);
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void BrowserModel::ReadNodeFlags(QTreeView* tree)
//{
//	jet::thread::ScopedMutex sm(m_mutex);
//	if (!m_rootItem)
//	{
//		return;
//	}
//
//	//generate mangled name for the file
//	String fileName;
//	if (HasSource(k_sourceClaraFiles))
//	{
//		for (u32 i = 0; i < Project::GetInstance()->GetClaraFileCount(); i++)
//		{
//			ClaraFile* cf = Project::GetInstance()->GetClaraFile(i);
//			if (cf && cf->IsOpen() && !cf->IsLibrary())
//			{
//				fileName += cf->GetName();
//			}
//		}
//	}
//	if (HasSource(k_sourceLibraries))
//	{
//		fileName += "Libraries";
//	}
//
//	if (fileName.empty())
//	{
//		return;
//	}
//
//	fileName = Project::GetInstance()->GetProjectPath() + "/" + fileName + ".els";
//
//
//	QFile in(fileName.c_str());
//	if (!in.open(QIODevice::ReadOnly))
//	{
//		PINFO("cannot open editor-level-settings file - %s", fileName.c_str());
//		return;
//	}
//
//	QJsonObject rootObject;
//
//	QByteArray doc = in.readAll();
//	QJsonDocument document = QJsonDocument::fromBinaryData(doc);
//	if (!document.isNull())
//	{
//		rootObject = document.object();
//	}
//	else
//	{
//		document = QJsonDocument::fromJson(doc);
//		rootObject = document.object();
//	}
//
//	Messenger::BlockAllMessages(true);
//
//	std::vector<std::pair<TreeItem*, QModelIndex> > parents;
//	parents.reserve(10000);
//	parents.push_back(std::make_pair(m_rootItem, QModelIndex()));
//	for (u32 i = 0; i < parents.size(); i++)
//	{
//		TreeItem* item = parents[i].first;
//		//copy Index DONOT TAKE A REFERENCE because the reference will be invalid when the vector resizes !!! 
//		QModelIndex index = parents[i].second;
//		{
//			ClaraNode* node = item->GetClaraNode();
//			if (node)
//			{
//				const Path& path = node->GetPath();
//
//				QJsonValue value = rootObject.value(path.GetAsString().c_str());
//				if (!value.isNull())
//				{
//					QJsonObject v = rootObject.value(path.GetAsString().c_str()).toObject();
//					QJsonValue visible = v["visible"];
//					QJsonValue expanded = v["expanded"];
//
//					node->SetVisible(visible.toBool(true));
//					if (tree && expanded.toBool(false))
//					{
//						auto proxyModel = dynamic_cast<TreeProxyFilterModel*>(tree->model());
//						PASSERT(proxyModel);
//						tree->expand(proxyModel->mapFromSource(index));
//					}
//				}
//			}
//			else if (tree)
//			{
//				tree->setExpanded(index, true);
//			}
//
//			for (u32 c = 0; c < item->GetChildCount(); c++)
//			{
//				parents.push_back(std::make_pair(item->GetChild(c), this->index(c, 0, index)));
//			}
//		}
//	}
//	Messenger::BlockAllMessages(false);
//
//	if (HasSource(k_sourceLibraries))
//	{
//		return;
//	}
//	// load transform
//	GLWidget* w = GetGLWidget(this);
//	if (w != 0 && w->GetCamera() != 0)
//	{
//
//		jet::scene::Camera* cam = w->GetCamera();
//		math::vec3f p;
//		math::quatf rot;
//		QJsonObject c = rootObject["__camera__"].toObject();
//		if (!c.isEmpty())
//		{
//			p.x = c["pos_x"].toDouble();
//			p.y = c["pos_y"].toDouble();
//			p.z = c["pos_z"].toDouble();
//
//			rot.x = c["rot_x"].toDouble();
//			rot.y = c["rot_y"].toDouble();
//			rot.z = c["rot_z"].toDouble();
//			rot.w = c["rot_w"].toDouble();
//			rot.normalize();
//			cam->SetTransform(p, rot);
//		}
//	}
//}
