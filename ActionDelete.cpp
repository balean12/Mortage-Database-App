#include "ActionDelete.h"

void ActionDelete::executeUndo()
{
	this->repo.addVictim(this->removedVictim);
}

void ActionDelete::executeRedo()
{
	this->repo.deleteVictim(this->removedVictim.getName());
}

