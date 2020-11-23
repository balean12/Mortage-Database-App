#include "Repository.h"
#include <assert.h>
#include <algorithm>
using namespace std;
int Repository::addVictim(const Victim& victim)
{	
	if (this->findVictimINT(victim.getName()) != -1)
		return 0;
	this->victims.push_back(victim);
	return 1;
}

//returns 0 if position was invalid and 1 if the Victim was deleted
int Repository::deleteVictim(const std::string& name)
{
	int posOfVictim = findVictimINT(name);
	if (posOfVictim == -1)
		return 0;
	this->victims.erase(this->victims.begin() + posOfVictim);
	return 1;

}

int Repository::updateVictim(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto)
{
	Victim victimToUpdate = findVictimByName(name);
	int position = findVictimINT(name);
	if (position == -1)
		return 0;
	else
	{	
		this->victims[position].setPlaceOfBirth(newPlaceOfOrigin);
		this->victims[position].setAge(newAge);
		this->victims[position].setPhoto(newPhoto);
	}
	return 1;
}

Victim Repository::findVictimByName(const std::string& name)
{	
	/*for (int i = 0; i < this->victims.size(); i++)
		if (this->victims[i].getName().compare(name) == 0)
			return this->victims[i];*/
	
	for (auto victim : this->victims) {
		if (victim.getName() == name)
			return victim;
	}
	return Victim{};
		 
}
int Repository::findVictimINT(const std::string& name)
{
	for (int i = 0; i < this->victims.size(); i++)
		if (this->victims[i].getName() == name)
			return i;
	return -1;
		 
}

std::vector<Victim> Repository::getVictims() const
{
	/*try {
		return this->victims;
	}
	catch (exception&) {};*/
	return this->victims;
}

void Repository::iterator()
{
	this->iter = this->victims.begin();
}

Victim Repository::getCurrentVictim()
{
	return *this->iter;
}

void Repository::next()
{
	if (*this->iter == this->victims.back())
		this->iterator();
	else ++this->iter;
}




