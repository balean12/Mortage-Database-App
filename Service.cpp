#include "Service.h"
#include <vector>
#include "victimValidator.h"
#include "Exceptions.h"
#include "ActionAdd.h"
#include "Action.h"
#include "ActionDelete.h"
#include "ActionUpdate.h"
#include "ActionSave.h"
using namespace std;
std::vector<Victim> Service::getAllVictimsInRepo() const
{	
	return this->repo.getVictims();
}

void Service::addVictimToRepository(const std::string& name, const std::string& placeOfOrigin, const int age, const std::string& photo)
{
	
	Victim v{ name, placeOfOrigin, age, photo };
	VictimValidator validator{};
	validator.validateVictim(v);
	if (this->repo.findVictimByName(name) != Victim{})
		throw ServiceException("Victim already added!");
	
	ActionAdd action{ this->repo, v };
	std::unique_ptr<Action> pAdd = std::make_unique<ActionAdd>(action);
	
	if (!this->undo_redo) {
		this->undoStack.push_back(move(pAdd));
		//reinitialize redo stack;
		this->redoStack = vector<unique_ptr<Action>>();
	}
	this->repo.addVictim(v);
}

void Service::deleteVictimFromRepo(const std::string& name)
{
	if (name == "")
		throw ValidatorException("Empty name field! \n");
	if (this->repo.findVictimByName(name) == Victim{})
		throw ServiceException("Victim not existent! \n");
	
	Victim vict = this->repo.findVictimByName(name);
	ActionDelete action{ this->repo, vict };
	unique_ptr<Action> pRemove = make_unique<ActionDelete>(action);
	if (!this->undo_redo) {
		this->undoStack.push_back(move(pRemove));
		this->redoStack = vector<unique_ptr<Action>>();
	}
	this->repo.deleteVictim(name);
	this->transferList.deleteFromTransferList(vict);
}

void Service::updateVictimFromRepo(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto)
{
	if (name == "" || newPlaceOfOrigin == "" || newAge <=0 || newPhoto== "")
		throw ValidatorException("Incorrect Input! \n");
	if (this->repo.findVictimByName(name) == Victim{})
		throw ServiceException("Victim not existent! \n");
	Victim newVict = Victim{ name, newPlaceOfOrigin, newAge ,newPhoto };
	Victim vict = this->repo.findVictimByName(name);

	ActionUpdate action { this->repo, vict, newVict };
	unique_ptr<Action> pUpdate = make_unique<ActionUpdate>(action);
	if (!this->undo_redo) {
		this->undoStack.push_back(move(pUpdate));
		this->redoStack = vector<unique_ptr<Action>>();
	}
	this->repo.updateVictim(name, newPlaceOfOrigin, newAge, newPhoto);
}

std::vector<Victim> Service::filteredList(std::string place, int age)
{
	std::vector<Victim> victims{};
	for (auto& v : this->getAllVictimsInRepo()) {
		if (v.getPlaceOfOrigin() == place && v.getAge() < age)
			victims.push_back(v);
	}
	return victims;
}

void Service::getTransferListApp() const
{
	this->transferList.getAll();
}

void Service::addToTransferListService(const std::string& name)
{
	if (name == "")
		throw ServiceException("Empty name! \n");
	Victim victim = this->repo.findVictimByName(name);
	VictimValidator validator{};
	validator.validateVictim(victim);
	if (victim == Victim{})
		throw ServiceException("Victim not existent! \n");

	ActionSave action{ this->transferList, victim };
	std::unique_ptr<Action> pSave = std::make_unique<ActionSave>(action);
	
	if (!this->undo_redo_transferList) {
		this->undoStackTransferList.push_back(move(pSave));
		//reinitialize redo stack;
		this->redoStackTransferList = vector<unique_ptr<Action>>();
	}
	this->transferList.addToTransferList(victim);
}
void Service::deleteFromTransferList(const std::string& name)
{
	if (name == "")
		throw ServiceException("Empty name! \n");
	Victim victim = this->repo.findVictimByName(name);
	VictimValidator validator{};
	validator.validateVictim(victim);
	if (victim == Victim{})
		throw ServiceException("Victim not existent! \n");

	this->transferList.deleteFromTransferList(victim);
}
std::vector<Victim> Service::getAllSaved() const
{
	return this->transferList.getAllVector();
}
void Service::iterator()
{
	this->repo.iterator();
}
void Service::next()
{	
		this->repo.next();
}

Victim Service::getCurrentFromIterator()
{
	return repo.getCurrentVictim();
}

void Service::undo()
{
	if (undoStack.size() == 0) {
		throw std::exception("Cannot undo!");
	}
	std::unique_ptr<Action> act = move(undoStack.back());
	undo_redo = true;
	act->executeUndo();
	undo_redo = false;
	redoStack.push_back(move(act));
	undoStack.pop_back();
}

void Service::redo()
{
	if (redoStack.size() == 0)
	{
		throw std::exception("Cannot Redo!");
	}
	std::unique_ptr<Action> act = move(redoStack.back());
	undo_redo = true;
	act->executeRedo();
	undo_redo = false;
	undoStack.push_back(move(act));
	redoStack.pop_back();
}
void Service::undoTransferList()
{
	if (undoStackTransferList.size() == 0) {
		throw std::exception("Cannot undo!");
	}
	std::unique_ptr<Action> act = move(undoStackTransferList.back());
	undo_redo_transferList = true;
	act->executeUndo();
	undo_redo_transferList = false;
	redoStackTransferList.push_back(move(act));
	undoStackTransferList.pop_back();
}

void Service::redoTransferList()
{
	if (redoStackTransferList.size() == 0)
	{
		throw std::exception("Cannot Redo!");
	}
	std::unique_ptr<Action> act = move(redoStackTransferList.back());
	undo_redo_transferList = true;
	act->executeRedo();
	undo_redo_transferList = false;
	undoStackTransferList.push_back(move(act));
	redoStackTransferList.pop_back();
}
