#include "VictimDesigner.h"
#include "Victim.h"
#include "PictureDelegate.h"
#include <vector>
#include "Exceptions.h"
#include <qmessagebox.h>
#include <QSortFilterProxyModel>
#include <qboxlayout.h>
#include <qpieseries.h>
#include <qchartview.h>
#include <qchartglobal.h>
#include <qpieslice.h>
#include <qmediaplayer.h>
#include <QHBoxLayout>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieslice.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <qshortcut.h>
#include "DialogVictimView.h"
#include "qicon.h"
using namespace std;
using namespace QtCharts;
VictimDesigner::VictimDesigner(Service& service, QWidget* parent)
	: QMainWindow(parent), service{ service }
{
	ui.setupUi(this);
	this->colorsAndMagic();
	this->populateVictimList();
	this->populateSavedVictimsList();
	this->connectSignalsAndSlots();
	this->charts();
	this->currentPos = 0;
	this->setupTableView();
	//this->tableModel = new VictimsTableModel{ this->service.getAllSaved() };
	
}

void VictimDesigner::populateVictimList()
{

	this->ui.victimsListWidget->clear();

	vector<Victim> allVIctims = this->service.getAllVictimsInRepo();
	for (Victim& v : allVIctims)
		this->ui.victimsListWidget->addItem(QString::fromStdString(v.getName()) + " - " + QString::fromStdString(v.getPlaceOfOrigin()) + " - " + QString::fromStdString(to_string(v.getAge())) + " - "
			+ QString::fromStdString(v.getPhoto()));
}

void VictimDesigner::populateSavedVictimsList()
{
	this->ui.savedListWidget->clear();
	try {
		vector<Victim> allVIctims = this->service.getAllSaved();
		for (Victim& v : allVIctims)
			this->ui.savedListWidget->addItem(QString::fromStdString(v.getName()) + " - " + QString::fromStdString(v.getPlaceOfOrigin()) + " - " + QString::fromStdString(to_string(v.getAge())) + " - "
				+ QString::fromStdString(v.getPhoto()));
	}
	catch (RepositoryException & repositoryException)
	{
		QMessageBox::critical(this, "Populate Error!", repositoryException.what());
	}
}

void VictimDesigner::connectSignalsAndSlots()
{
	QObject::connect(this->ui.victimsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int indexSelectedVictim = this->getSelectedIndex();
		if (indexSelectedVictim < 0)
			return;
		Victim victim = this->service.getAllVictimsInRepo()[indexSelectedVictim];
		this->ui.lineEditName->setText(QString::fromStdString(victim.getName()));
		this->ui.lineEditPlace->setText(QString::fromStdString(victim.getPlaceOfOrigin()));
		this->ui.lineEditAge->setText(QString::fromStdString(to_string(victim.getAge())));
		this->ui.lineEditPhoto->setText(QString::fromStdString(victim.getPhoto()));
		});


	QObject::connect(this->ui.pushButtonAdd, &QPushButton::clicked, this, &VictimDesigner::addVictim);
	QObject::connect(this->ui.pushButtonDelete, &QPushButton::clicked, this, &VictimDesigner::deleteVictim);
	QObject::connect(this->ui.pushButtonUpdate, &QPushButton::clicked, this, &VictimDesigner::updateVictim);
	QObject::connect(this->ui.pushButtonExit, &QPushButton::clicked, [this]() {exit(1); });

	QObject::connect(this->ui.pushButtonSave, &QPushButton::clicked, this, &VictimDesigner::save);
	QObject::connect(this->ui.pushButton_2, &QPushButton::clicked, this, &VictimDesigner::next);
	QObject::connect(this->ui.pushButtonFilter, &QPushButton::clicked, this, &VictimDesigner::filter);
	QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &VictimDesigner::open);
	
	QObject::connect(this->ui.pushButtonUndo, &QPushButton::clicked, this, &VictimDesigner::undo);
	QObject::connect(this->ui.pushButton_4, &QPushButton::clicked, this, &VictimDesigner::redo);
	QObject::connect(this->ui.pushButtonUndoT, &QPushButton::clicked, this, &VictimDesigner::undoTransfer);
	QObject::connect(this->ui.pushButtonRedoT, &QPushButton::clicked, this, &VictimDesigner::redoTransfer);


	QObject::connect(this->ui.pushButtonView, &QPushButton::clicked, this, &VictimDesigner::openView);
	QObject::connect(this->ui.pushButton_3, &QPushButton::clicked, this, &VictimDesigner::playMusic);

	
	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this->ui.pushButtonUndo);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &VictimDesigner::undo);
	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this->ui.pushButton_4);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &VictimDesigner::redo);
	
}

int VictimDesigner::getSelectedIndex() const
{

	QModelIndexList selectedIndexes = this->ui.victimsListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) {
		this->ui.lineEditName->clear();
		this->ui.lineEditPlace->clear();
		this->ui.lineEditAge->clear();
		this->ui.lineEditPhoto->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}
void VictimDesigner::setupTableView()
{
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
void VictimDesigner::deleteVictim()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0) {
		QMessageBox::critical(this, "Error", "No victim was selected!");
		return;
	}

	Victim v = this->service.getAllVictimsInRepo()[selectedIndex];
	try {
		this->service.deleteVictimFromRepo(v.getName());
		this->populateVictimList();
		this->populateSavedVictimsList();
		this->setupTableView();
	}
	catch (ValidatorException & validatorException) {
		QMessageBox::critical(this, "Error!", validatorException.what());
	}
	catch (ServiceException & serviceException)
	{
		QMessageBox::critical(this, "Error!", serviceException.what());
		//cout << serviceException.what();
	}
	catch (RepositoryException & repositoryException)
	{
		QMessageBox::critical(this, "Error!", repositoryException.what());
		//cout << repositoryException.what();
	}
	catch (...)
	{
		QMessageBox::critical(this, "Error!", "Unexpected Error");
		//cout << "Unexpected error" << "\n";
	}
}
void VictimDesigner::updateVictim()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No victim was selected!");
		return;
	}
	Victim v = this->service.getAllVictimsInRepo()[selectedIndex];
	string place = this->ui.lineEditPlace->text().toStdString();
	int a = this->ui.lineEditAge->text().toInt();
	string photo = this->ui.lineEditPhoto ->text().toStdString();
	try {
		this->service.updateVictimFromRepo(v.getName(), place, a, photo);
		if (v.getAge() == a && v.getPhoto() == photo && v.getPlaceOfOrigin() == place) {
			QMessageBox::information(this, "Attention", "In order to update a victim's details, make sure to make at least one change before pressing the update button!");
			return;
		}
		this->populateVictimList();
	}
	catch (ValidatorException & validatorException) {
		QMessageBox::critical(this, "Error!", validatorException.what());
	}
	catch (ServiceException & serviceException)
	{
		QMessageBox::critical(this, "Error!", serviceException.what());
		//cout << serviceException.what();
	}
	catch (RepositoryException & repositoryException)
	{
		QMessageBox::critical(this, "Error!", repositoryException.what());
		//cout << repositoryException.what();
	}
	catch (...)
	{
		QMessageBox::critical(this, "Error!", "Unexpected Error");
		//cout << "Unexpected error" << "\n";
	}
}
void VictimDesigner::save()
{
	string name = this->ui.lineEditName_2->text().toStdString();
	try {
		this->service.addToTransferListService(name);
		this->populateSavedVictimsList();
		this->setupTableView();
		int lastElement = this->service.getAllSaved().size() - 1;
		this->ui.savedListWidget->setCurrentRow(lastElement);
	}
	catch (...)
	{
		QMessageBox::critical(this, "Error!", "Unexpected Error");
		//cout << "Unexpected error" << "\n";

	}
}
void VictimDesigner::next()
{	
	if (this->service.getAllVictimsInRepo().size() == 0) {
		QMessageBox::critical(this, "Error!", "List empty");
		return;
	}
	
	Victim victim = this->service.getAllVictimsInRepo()[currentPos];
	this->ui.lineEditName_2->setText(QString::fromStdString(victim.getName()));
	this->ui.lineEditPlace_2->setText(QString::fromStdString(victim.getPlaceOfOrigin()));
	this->ui.lineEditAge_2->setText(QString::fromStdString(to_string(victim.getAge())));
	this->ui.lineEditPhoto_2->setText(QString::fromStdString(victim.getPhoto()));
	
	if (this->currentPos == this->service.getAllVictimsInRepo().size()-1)
		this->currentPos = 0;
	else currentPos++;

}
void VictimDesigner::filter()
{
	QListWidget* filterListW = new QListWidget{};
	filterListW->clear();
	vector<Victim> filteredVictims = this->service.filteredList(this->ui.lineEditPlaceFilter->text().toStdString(),
		this->ui.lineEditAgeFilter->text().toInt());
	for (Victim& v : filteredVictims)
		filterListW->addItem(QString::fromStdString(v.getName()) + " - " + QString::fromStdString(v.getPlaceOfOrigin()) + " - " + QString::fromStdString(to_string(v.getAge())) + " - "
			+ QString::fromStdString(v.getPhoto()));
	filterListW->show();
}
void VictimDesigner::open()
{
	this->service.getTransferListApp();
}
void VictimDesigner::openView()
{
	DialogVictimView* view = new DialogVictimView{ this->service.getTransferList(), this->service};
	view->show();
}
void VictimDesigner::undo()
{
	try {
		this->service.undo();
		this->populateVictimList();
	}
	catch (std::exception ex) {
		QMessageBox::critical(this, "Error!", ex.what());
	}
}
void VictimDesigner::redo()
{
	try {
		this->service.redo();
		this->populateVictimList();
	}
	catch (std::exception ex) {
		QMessageBox::critical(this, "Error!", ex.what());
	}

}
void VictimDesigner::undoTransfer()
{
	try {
		this->service.undoTransferList();
		this->populateSavedVictimsList();
	}
	catch (std::exception ex) {
		QMessageBox::critical(this, "Error!", ex.what());
	}

}
void VictimDesigner::redoTransfer()
{
	try {
		this->service.redoTransferList();
		this->populateSavedVictimsList();
	}
	catch (std::exception ex) {
		QMessageBox::critical(this, "Error!", ex.what());
	}
}
void VictimDesigner::charts()
{
	QHBoxLayout* layout = new QHBoxLayout{ this };
	QPieSeries* pieSeriesAge = new QPieSeries();
	vector<QPieSlice*> slicesVectorAge;

	vector<Victim> victims = this->service.getAllVictimsInRepo();
	vector<int> ages;

	for (int i = 0; i < victims.size(); i++) {
		int currentAge = victims[i].getAge();
		int ageAppearance = 1;
		for (int j = 0; j < ages.size(); j++)
			if (ages[j] == currentAge)
				ageAppearance = 0;
		if (ageAppearance == 1)
			ages.push_back(currentAge);
	}

	for (int i = 0; i < ages.size(); i++) {
		int numberPerAppearance = 0;
		for (int j = 0; j < victims.size(); j++)
			if (victims[j].getAge() == ages[i])
				numberPerAppearance++;
		string ageAndNumber = to_string(ages[i]) + ":" + to_string(numberPerAppearance);
		pieSeriesAge->append(ageAndNumber.c_str(), numberPerAppearance);
		slicesVectorAge.push_back(pieSeriesAge->slices().at(i));
		slicesVectorAge[i]->setLabelVisible();
	}

	QChart* chartAgeNumbers = new QChart();
	chartAgeNumbers->setTheme(chartAgeNumbers->ChartThemeDark);
	chartAgeNumbers->addSeries(pieSeriesAge);
	chartAgeNumbers->setTitle("Victims statistics by age");

	QChartView* chartViewAgeNumbers = new QChartView(chartAgeNumbers);
	chartViewAgeNumbers->setRenderHint(QPainter::Antialiasing);
	chartViewAgeNumbers->setMinimumWidth(499);

	QVBoxLayout* chartLayoutAgeNumbers = new QVBoxLayout();
	chartLayoutAgeNumbers->addWidget(chartViewAgeNumbers);

	layout->addLayout(chartLayoutAgeNumbers);
	this->ui.Charts->setLayout(layout);
}
void VictimDesigner::playMusic()
{
	QMediaPlayer* player = new QMediaPlayer();
	player->setMedia(QUrl::fromLocalFile("hell.mp3"));
	player->setVolume(50);
	player->play();
}
void VictimDesigner::colorsAndMagic()
{
	//background
	ui.centralWidget->setAutoFillBackground(true);
	setStyleSheet("#centralWidget {background-image: url(./blood.jpg)}");
	//setStyleSheet("#tabWidget {background-image: url(./blood.jpg)}");
	ui.tabWidget->setAutoFillBackground(true);
	ui.tab->setAutoFillBackground(true);
	//ui.tabWidget->setStyleSheet("background-image: url(./blood.jpg)");
	//ui.centralWidget->setAutoFillBackground(false);
	ui.victimsListWidget->setStyleSheet("font: 15pt; color: white; background-image: url(./morgue.jpg)");
	ui.victimsListWidget->foregroundRole();
	ui.savedListWidget->setStyleSheet("font: 15pt; color: black; background-image: url(./hell.jpg)");

	//lineedits
	ui.lineEditName->setStyleSheet("color: white; background-color: black");
	ui.lineEditPlace->setStyleSheet("color: white; background-color: black");
	ui.lineEditAge->setStyleSheet("color: white; background-color: black");
	ui.lineEditPhoto->setStyleSheet("color: white; background-color: black");
	ui.lineEditName_2->setStyleSheet("color: white; background-color: black");
	ui.lineEditPlace_2->setStyleSheet("color: white; background-color: black");
	ui.lineEditAge_2->setStyleSheet("color: white; background-color: black");
	ui.lineEditPhoto_2->setStyleSheet("color: white; background-color: black");
	ui.lineEditAgeFilter->setStyleSheet("color: white; background-color: black");
	ui.lineEditPlaceFilter->setStyleSheet("color: white; background-color: black");

	//buttons
	ui.pushButton->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonAdd->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonDelete->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButton_3->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButton_2->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonUndo->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonSave->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonUpdate->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonExit->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonView->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonFilter->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonRedoT->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButtonUndoT->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	ui.pushButton_4->setStyleSheet("color: white; background-color: rgb(115,0,0)");
	

	//icon
	this->setWindowIcon(QIcon("Resources/coroner.png"));
}
void VictimDesigner::addVictim()
{
	string name = this->ui.lineEditName->text().toStdString();
	string place = this->ui.lineEditPlace->text().toStdString();
	int a = this->ui.lineEditAge->text().toInt();
	string photo = this->ui.lineEditPhoto->text().toStdString();
	try {
		this->service.addVictimToRepository(name, place, a, photo);
		this->populateVictimList();
		int lastElement = this->service.getAllVictimsInRepo().size() - 1;
		this->ui.victimsListWidget->setCurrentRow(lastElement);
	}
	catch (ValidatorException & validatorException) {
		QMessageBox::critical(this, "Error!", validatorException.what());
	}
	catch (ServiceException & serviceException)
	{
		QMessageBox::critical(this, "Error!", serviceException.what());
		//cout << serviceException.what();
	}
	catch (RepositoryException & repositoryException)
	{
		QMessageBox::critical(this, "Error!", repositoryException.what());
		//cout << repositoryException.what();
	}
	catch (...)
	{
		QMessageBox::critical(this, "Error!", "Unexpected Error");
		//cout << "Unexpected error" << "\n";

	}
}
