#pragma once
#include "Action.h"
#include "TransferListInterface.h"
class ActionSave :
	public Action
{
	private:
	Victim savedVictim;
	TransferInterface& transf;
public:
	ActionSave(TransferInterface& transf, Victim savedVictim) : transf{ transf }, savedVictim{ savedVictim }{};
	void executeUndo() override;
	void executeRedo() override;
};

