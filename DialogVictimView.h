#pragma once

#include <QWidget>
#include "ui_DialogVictimView.h"
#include "Service.h"
#include "VictimsTableModel.h"
#include "Observer.h"
#include "TransferListInterface.h"

class DialogVictimView : public QWidget, public Observer
{
	Q_OBJECT

public:
	TransferInterface& transList;
public:
	DialogVictimView(TransferInterface& t, Service& service, QWidget *parent = Q_NULLPTR);
	~DialogVictimView();
	void update() override;
private:
	Service& service;
	VictimsTableModel* tableModel;
	Ui::DialogVictimView ui;

};
