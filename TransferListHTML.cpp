#include "TransferListHTML.h"
#include <fstream>
#include "Exceptions.h"
#include <Windows.h>
#include <shellapi.h>



int TransferHTML::addToTransferList(const Victim& victim)
{
	this->savedVictims.push_back(victim);
	std::ofstream openedFile(this->filename);
	if (!openedFile.is_open())
		throw TransferListException("The file could not be opened!\n");
	openedFile << "<!DOCTYPE html> \n" << "<html> \n";
	openedFile << "<head>\n" << " <title> Victims </title> \n" << "</head>\n";
	openedFile << "<body>\n" << "<table border=\"1\" bgcolor=\"#82E0AA\" align=\"center\">\n";
	openedFile << "<tr>\n <td>Name</td>\n" << "<td>Place of Origin</td>\n" << " <td>Age</td>\n" << "<td>Photo Link</td>\n";
	
	for (auto& victim : this->savedVictims)
	{
		openedFile << "<tr>\n";
		openedFile << "<td>" << victim.getName() << "</td> \n";
		openedFile << "<td>" << victim.getPlaceOfOrigin() << "</td> \n";
		openedFile << "<td>" << victim.getAge() << "</td> \n";
		openedFile << "<td> <a href=" << victim.getPhoto() << ">Link </a> </td> \n";
	}
	openedFile << "</table>\n" << "</body> \n" << "</html> \n";
	openedFile.close();
	return 0;
}

int TransferHTML::deleteFromTransferList(const Victim& victim)
{
	std::vector<Victim> victims;
	for (int i = 0; i < this->savedVictims.size(); i++) {
		if (this->savedVictims[i].getName() != victim.getName())
			victims.push_back(savedVictims[i]);
	}
	std::ofstream openedFile(this->filename);
	if (!openedFile.is_open())
		throw TransferListException("The file could not be opened!\n");
	openedFile << "<!DOCTYPE html> \n" << "<html> \n";
	openedFile << "<head>\n" << " <title> Victims </title> \n" << "</head>\n";
	openedFile << "<body>\n" << "<table border=\"1\" bgcolor=\"#82E0AA\" align=\"center\">\n";
	openedFile << "<tr>\n <td>Name</td>\n" << "<td>Place of Origin</td>\n" << " <td>Age</td>\n" << "<td>Photo Link</td>\n";

	for (auto& victim : victims)
	{
		openedFile << "<tr>\n";
		openedFile << "<td>" << victim.getName() << "</td> \n";
		openedFile << "<td>" << victim.getPlaceOfOrigin() << "</td> \n";
		openedFile << "<td>" << victim.getAge() << "</td> \n";
		openedFile << "<td> <a href=" << victim.getPhoto() << ">Link </a> </td> \n";
	}
	openedFile << "</table>\n" << "</body> \n" << "</html> \n";
	openedFile.close();
	return 0;
}

void TransferHTML::getAll()
{
	std::string stringFilename= '"' + this->filename + '"';
	ShellExecuteA(NULL, NULL, "opera.exe", stringFilename.c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::vector<Victim> TransferHTML::getAllVector()
{
	return this->savedVictims;
}




