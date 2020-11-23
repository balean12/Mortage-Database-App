#include "TransferListCSV.h"
#include <fstream>
#include "Exceptions.h"
#include <Windows.h>
#include <shellapi.h>


int TransferListCSV::addToTransferList(const Victim& victim)
{	
	std::ofstream f(filename, std::ios::app);
	if (!f.is_open())
		//change to exception
		return 0;

	f << victim << std::endl;
	f.close();
	this->notify();
}

int TransferListCSV::deleteFromTransferList(const Victim& victim)
{
	std::ifstream f(filename);
	
	if (!f.is_open())
		//change to exception
		return 0;
	std::vector<Victim> victims;
	Victim v{};
	while (f >> v)
		victims.push_back(v);
	f.close();
	std::ofstream g(filename);
	for (int i = 0; i < victims.size(); i++)
		if (victims[i].getName() != victim.getName())
			g << victims[i] << std::endl;
	
	g.close();
	//observer;
	this->notify();
	
}

void TransferListCSV::getAll ()
{
	std::string stringFilename= '"' + this->filename + '"';
	ShellExecuteA(NULL, NULL, "notepad.exe", stringFilename.c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::vector<Victim> TransferListCSV::getAllVector()
{
	std::vector<Victim> victims{};
	Victim v{};
	std::ifstream f(this->filename);
	if (!f.is_open())
		throw RepositoryException("File could not be open!");
	while (f >> v)
	{
		victims.push_back(v);
	}
	return victims;
}

