//#pragma once
//
//#include <QAbstractItemModel>
//
//class BrowserModel : public QAbstractItemModel
//{
//	Q_OBJECT
//
//public:
//	BrowserModel(QObject* parent = nullptr);
//	~BrowserModel();
//
//	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
//	QVariant data(const QModelIndex& index, int role) const override;
//	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
//
//	Qt::ItemFlags flags(const QModelIndex& index) const override;
//
//	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
//	QModelIndex parent(const QModelIndex& index) const override;
//
//	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
//	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
//
//	Qt::DropActions supportedDropActions() const override;
//	bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;
//	QMimeData* mimeData(const QModelIndexList& indexes) const override;
//	QStringList mimeTypes() const override;
//
//public slots:
//	void expand(const QModelIndex& index);
//	void collapse(const QModelIndex& index);
//};
