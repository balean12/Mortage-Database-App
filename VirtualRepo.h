#pragma once
#include "Victim.h"
#include <vector>
#include <string>
class RepoInterface
{
public:
	virtual int addVictim(const Victim& victim) = 0;
	virtual int deleteVictim(const std::string& name) = 0;
	virtual int updateVictim(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto) = 0;
	virtual Victim findVictimByName(const std::string& name) = 0;
	virtual std::vector<Victim> getVictims() const = 0;
	
	virtual void iterator() = 0;
	virtual Victim getCurrentVictim() = 0;
	virtual void next() = 0;
	virtual bool isEmpty() = 0;
	//virtual int getCurrent() = 0;
};