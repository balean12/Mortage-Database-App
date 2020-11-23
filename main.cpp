#include "VictimDesigner.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Service.h"
#include "TransferListInterface.h"
#include "TransferListCSV.h"
#include "TransferListHTML.h"
#include "Victim.h"
#include "FileRepo.h"
#include "Tests.h"
#include <assert.h>
#include <crtdbg.h>
#include <fstream>
#include <exception>
#include "VictimDesigner.h"
using namespace std;
string determineMyListType(string fileName)
{
	std::size_t positionFound = fileName.rfind(".");
	if (positionFound == std::string::npos)
		throw exception("Invalid file name\n");

	return fileName.substr(positionFound, std::string::npos);
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::string configFileName = "configuration.txt";

	std::fstream configurationFile;
	configurationFile.open(configFileName, std::fstream::in | std::fstream::out | std::fstream::app);

	std::ifstream file(configFileName);
	std::string fileName, myListFileName, myListFileType;
	getline(file, fileName);
	getline(file, myListFileName);
	file.close();

	TransferInterface* myListRepo = nullptr;
	RepoInterface* repo = nullptr;	

	if (fileName == "inMemory") repo = new Repository{};
	else repo = new FileRepo{ fileName };

	myListFileType = determineMyListType(myListFileName);

	if (myListFileType == ".csv") myListRepo = new TransferListCSV{ myListFileName };
	else myListRepo = new TransferHTML{ myListFileName };
	
	Service service{ *repo, *myListRepo };
	VictimDesigner gui{service};
	gui.show();


	return a.exec();
}
