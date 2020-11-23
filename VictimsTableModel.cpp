#include "VictimsTableModel.h"
#include <qfont.h>
#include <qbrush.h>
VictimsTableModel::VictimsTableModel(std::vector<Victim> victimsSaved, QObject* parent) : QAbstractTableModel{ parent }, victimsSaved{ victimsSaved }
{
}

int VictimsTableModel::rowCount(const QModelIndex& parent) const
{
	int victimNumber = this->victimsSaved.size();
	return victimNumber;
}

int VictimsTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant VictimsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	std::vector<Victim> victims = this->victimsSaved;

	//get the victim from the current row;
	if (row == victims.size())
		return QVariant();
	
	Victim victim = victims[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(victim.getName());
		case 1:
			return QString::fromStdString(victim.getPlaceOfOrigin());
		case 2:
			return QString::fromStdString(std::to_string(victim.getAge()));
		case 3:
			return QString::fromStdString(victim.getPhoto());
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 15, 10, true);
		//font.setBold(true);
		return font;
	}
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
			return QBrush{ QColor{0, 253, 190} };
	}
	return QVariant{};
}

QVariant VictimsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Name" };
			case 1:
				return QString{ "Place of Origin" };
			case 2:
				return QString{ "Age" };
			case 3:
				return QString{ "Photo" };
			default:
				break;
			}
		}
	}
		if (role == Qt::FontRole)
		{
			if (role == Qt::FontRole)
			{
				QFont font("Times", 15, 10, true);
				font.setBold(true);
				return font;
			}
		}
		return QVariant{};
}

Qt::ItemFlags VictimsTableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


