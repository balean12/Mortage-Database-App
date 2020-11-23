#pragma once
#include "Action.h"
#include "Victim.h"
#include "Repository.h"
class ActionAdd :
	public Action
{
private:
	Victim addedVictim;
	RepoInterface& repo;
public:
	ActionAdd(RepoInterface& repo, Victim addedVictim) : repo{ repo }, addedVictim{ addedVictim }{};
	void executeUndo() override;
	void executeRedo() override;
};

