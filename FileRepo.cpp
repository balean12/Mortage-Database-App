#include "FileRepo.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
FileRepo::FileRepo(string filename)
{
	this->filename = filename;
}
int FileRepo::addVictim(const Victim& victim)
{
	std::ofstream f(filename, std::ios::app);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	
	f << victim << std::endl;
	
	f.close();


}

int FileRepo::deleteVictim(const std::string& name)
{
	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");

	vector<Victim> victims{};
	Victim v{};
	while (f >> v)
	{
		victims.push_back(v);
	}
	int counter = 0;
	for (auto v : victims) {
		counter += 1;
		if (v.getName() == name) {
			victims.erase(victims.begin() + counter - 1);
		}
	}
	f.close();
	ofstream g(filename);
	if (!g.is_open())
		throw RepositoryException("File could not be open!");
	for (auto v : victims) {
		g << v << std::endl;
	}
	g.close();
}

int FileRepo::updateVictim(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto)
{
	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");

	vector<Victim> victims{};
	Victim v{};
	while (f >> v)
	{
		victims.push_back(v);
	}
	Victim newVictim{ name, newPlaceOfOrigin, newAge, newPhoto };
	vector<Victim> vect{};
	for (auto v : victims) {
		if (v.getName() == newVictim.getName())
			vect.push_back(newVictim);
		else {
			vect.push_back(v);
		}
	}
	f.close();
	ofstream g(filename);
	if (!g.is_open())
		throw RepositoryException("File could not be open!");
	for (auto v : vect) {
		g << v << std::endl;
	}
	g.close();
}

Victim FileRepo::findVictimByName(const std::string& name)
{
	vector<Victim> victims{};
	Victim v{};
	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	while (f >> v)
	{
		victims.push_back(v);
	}
	for (auto victim : victims) {
		if (victim.getName() == name)
			return victim;
	}
	return Victim{};
}

std::vector<Victim> FileRepo::getVictims() const
{
	vector<Victim> victims{};
	Victim v{};
	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	while (f >> v)
	{
		victims.push_back(v);
	}
	return victims;
}

Victim FileRepo::getCurrentVictim()
{
	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	std::vector<Victim> victims{};
	Victim v{};
	while (f >> v)
	{
		victims.push_back(v);
	}
	
	f.close();
	return victims[this->current];
}

void FileRepo::next()
{
	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	std::vector<Victim> victims{};
	Victim v{};
	while (f >> v)
	{
		victims.push_back(v);
	}
	if (victims[this->current] == victims[victims.size() - 1]) { this->iterator(); }
	else {
		this->current++;
	}
}

bool FileRepo::isEmpty()
{

	ifstream f(filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	std::vector<Victim> victims{};
	Victim v{};
	while (f >> v)
	{
		victims.push_back(v);
	}
	return(victims.size() == 0);
}
