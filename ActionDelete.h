#pragma once
#include "Action.h"
class ActionDelete :
	public Action
{
private:
	Victim removedVictim;
	RepoInterface& repo;
public:
	ActionDelete(RepoInterface& repo, Victim removedVictim) : repo{ repo }, removedVictim{ removedVictim }{};
	void executeUndo() override;
	void executeRedo() override;
};

