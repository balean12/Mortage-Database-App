#include "ActionSave.h"

void ActionSave::executeUndo()
{
	transf.deleteFromTransferList(savedVictim);
}

void ActionSave::executeRedo()
{
	this->transf.addToTransferList(savedVictim);
}
