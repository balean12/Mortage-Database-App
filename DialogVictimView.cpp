#include "DialogVictimView.h"
#include "VictimsTableModel.h"
#include "Service.h"
#include <QSortFilterProxyModel>
#include <qheaderview.h>
#include "PictureDelegate.h"
DialogVictimView::DialogVictimView(TransferInterface& t, Service& service, QWidget* parent)
	: QWidget(parent), service{ service }, transList{ t }
{
	ui.setupUi(this);
	this->setWindowIcon(QIcon("Resources/coroner.png"));
	this->transList.addObserver(this);
	// create and set a QSortFilterProxyModel and enable sorting
	this->tableModel = new VictimsTableModel{ this->service.getAllSaved() };
	QSortFilterProxyModel* proxyModel =
		new QSortFilterProxyModel{};
	
	proxyModel->setSourceModel(this->tableModel);
	ui.tableView->setSortingEnabled(true);

	ui.tableView->setModel(proxyModel);

	this->ui.tableView->setItemDelegate(new PictureDelegate{});
	
	ui.tableView->resizeColumnsToContents();
	ui.tableView->resizeRowsToContents();
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	//this->ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

DialogVictimView::~DialogVictimView()
{
	this->transList.removeObserver(this);
}

void DialogVictimView::update()
{
	this->tableModel = new VictimsTableModel{ this->service.getAllSaved() };
	QSortFilterProxyModel* proxyModel =
		new QSortFilterProxyModel{};

	proxyModel->setSourceModel(this->tableModel);
	ui.tableView->setSortingEnabled(true);

	ui.tableView->setModel(proxyModel);

	this->ui.tableView->setItemDelegate(new PictureDelegate{});

	ui.tableView->resizeColumnsToContents();
	ui.tableView->resizeRowsToContents();
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}
