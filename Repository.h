#pragma once
//#include "DynamicArray.h"
#include <vector>
#include <iterator>
#include "Victim.h"
#include "VirtualRepo.h"

class Repository : public RepoInterface
{
private:
	std::vector<Victim> victims;
	std::vector<Victim>::iterator iter;
	//friend class IteratorRepo;
public:
	/*
		Default constructor
		Initializes an object of type repository
	*/
	Repository() {}
	/*
		Adds a victim to the repository
		Input: victim - Victim.
		Output: the song is added to the repository
	*/
	int addVictim(const Victim& victim) override;

	/*
		Removes a victim from the repo
		Input: position of the victim
		Output: 1 if victim was deleted, 0 otherwise
	*/
	int deleteVictim(const std::string& name) override;
	
	
	int updateVictim(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto) override;

	/*
		Find a victim by name;
		Input: name - string
		Output: the victim found or NULL if no such victim found
	*/
	Victim findVictimByName(const std::string& name) override;
	
	/*Returns the position of a victim found by a given name*/
	int findVictimINT(const std::string& name);
	
	//Returns the whole dynamic vector containing all victims
	std::vector<Victim> getVictims() const override;

	//Iterator
	void iterator() override;
	Victim getCurrentVictim() override;
	void next() override;
	bool isEmpty() override { return victims.size() == 0; }
};