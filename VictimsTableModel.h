#pragma once
#include <qabstractitemmodel.h>
#include "FileRepo.h"
#include "VirtualRepo.h"
#include "Service.h"
class VictimsTableModel :
	public QAbstractTableModel
{
private:
	std::vector<Victim> victimsSaved;
public:
	VictimsTableModel(std::vector<Victim> victimsSaved, QObject* parent = NULL);
	~VictimsTableModel() {};

	//number of rows
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	//number of columns

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	//Value at a given position

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	//add header data
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	//will be called wehn a cell is edited

	//bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	//used to set certain properties of a cell
	Qt::ItemFlags flags(const QModelIndex& index) const override;



};

