#pragma once
#include "Action.h"
class ActionUpdate :
	public Action
{
private:
	Victim victim;
	Victim newVictim;
	RepoInterface& repo;
public:
	ActionUpdate(RepoInterface& repo, Victim victim, Victim newVictim) :
		repo{ repo }, victim{ victim }, newVictim{ newVictim }{};
	void executeUndo() override;
	void executeRedo() override;
};

