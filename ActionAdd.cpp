#include "ActionAdd.h"

void ActionAdd::executeUndo()
{
	this->repo.deleteVictim(this->addedVictim.getName());
}

void ActionAdd::executeRedo()
{
	this->repo.addVictim(this->addedVictim);
}
