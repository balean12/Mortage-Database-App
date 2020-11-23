#pragma once
#include "Repository.h"
#include "Victim.h"
#include "TransferListInterface.h"
#include "Action.h"
#include <vector>

class Service
{
private:
	RepoInterface& repo;
	TransferInterface& transferList;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;
	bool undo_redo;
	std::vector<std::unique_ptr<Action>> undoStackTransferList;
	std::vector<std::unique_ptr<Action>> redoStackTransferList;
	bool undo_redo_transferList = false;
public:
	//service constructor
	Service(RepoInterface& r, TransferInterface& l) : repo{ r }, transferList{ l } {}

	//returns the Repository
	RepoInterface& getRepo() const { return repo; }
	
	//returns the dynmaic vector from the repository
	std::vector<Victim> getAllVictimsInRepo() const;

	//Adds victim to repository
	void addVictimToRepository(const std::string& name, const std::string& placeOfOrigin, const int age, const std::string& photo);
	//Deletes a victim from repository
	void deleteVictimFromRepo(const std::string& name);
	//Updates a victim from repository
	void updateVictimFromRepo(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto);
	//filter victims
	std::vector<Victim> filteredList(std::string place, int age);

	//============== TransferList ==============

	//Returns the trasnfer list
	void getTransferListApp() const;
	//adds a new victim to transferlist
	void addToTransferListService(const std::string& name);
	//returns a vetor with the list
	void deleteFromTransferList(const std::string& name);
	std::vector<Victim> getAllSaved() const;
	TransferInterface& getTransferList() { return this->transferList; };
	void undoTransferList();
	void redoTransferList();
	
	//============== ITERATOR =============
	void iterator();
	//accesses the iterator and increases current, moving to the next element
	void next();
	//returns the current victim
	Victim getCurrentFromIterator();

	//=============== UNDO REDO ==============

	void undo();
	void redo();
};