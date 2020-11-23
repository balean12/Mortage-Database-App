#include "ActionUpdate.h"

void ActionUpdate::executeUndo()
{
	this->repo.updateVictim(victim.getName(), victim.getPlaceOfOrigin(), victim.getAge(), victim.getPhoto());
}

void ActionUpdate::executeRedo()
{
	this->repo.updateVictim(newVictim.getName(), newVictim.getPlaceOfOrigin(), newVictim.getAge(), newVictim.getPhoto());
}

