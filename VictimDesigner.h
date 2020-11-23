#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VictimDesigner.h"
#include "Service.h"
#include "VictimsTableModel.h"

class VictimDesigner : public QMainWindow
{
	Q_OBJECT

public:
	VictimDesigner(Service& service, QWidget *parent = Q_NULLPTR);

private:
	int currentPos;
	Service& service;
	VictimsTableModel* tableModel;
	Ui::VictimDesignerClass ui;

	void populateVictimList();
	void populateSavedVictimsList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void setupTableView();
	
	void addVictim();
	void deleteVictim();
	void updateVictim();

	void save();
	void next();
	void filter();
	void open();
	void openView();

	void undo();
	void redo();
	void undoTransfer();
	void redoTransfer();
	void charts();
	void playMusic();
	void colorsAndMagic();
};
