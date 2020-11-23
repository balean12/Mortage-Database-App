#include "Tests.h"
#include "FileRepo.h"
#include "TransferListCSV.h"
#include <exception>
void Tests::allTests()
{
	
	testDomain();
	testRepoInMemory();
	testRepoFile();
	testRepoFile_invalidNameFile();
	testServiceAllTests();
}

void Tests::testRepoInMemory()
{
	Repository repoInMemory;
	//=================== Test Add ===================;
	assert(repoInMemory.getVictims().size() == 0);
	int res1 = repoInMemory.addVictim(Victim("Jane", "Romania", 33, "asd.jpg"));
	int res2 = repoInMemory.addVictim(Victim("Jane", "Romania", 33, "asd.jpg"));
	assert(res1 == 1);
	assert(res2 == 0);
	repoInMemory.addVictim(Victim("Janed", "Germany", 43, "asadsd.jpg"));
	assert(repoInMemory.getVictims().size() == 2);
	
	//================ Test Find Victim with int returned ==============
	assert(repoInMemory.findVictimINT("Jane") == 0);
	assert(repoInMemory.findVictimINT("Flaviu") == -1);

	//================ Test Update ===========================
	assert(repoInMemory.updateVictim("Flaviu", "asds", 324, "asda.jpg") == 0);
	assert(repoInMemory.updateVictim("Jane", "dasd", 333, "asda") == 1);
	assert(repoInMemory.getVictims()[0].getName() == "Jane"); //.compare("Jane") == 0);
	assert(repoInMemory.getVictims()[0].getPlaceOfOrigin() == "dasd");//.compare("dasd") == 0);
	assert(repoInMemory.getVictims()[0].getAge() == 333);
	assert(repoInMemory.getVictims()[0].getPhoto() == "asda");//.compare("asda") == 0);
	
	//================= Test Delete =============================
	assert(repoInMemory.deleteVictim("Janeeeee") == 0);
	assert(repoInMemory.deleteVictim("Janed") == 1);

	//================= Test Find Victim Name ======================
	repoInMemory.addVictim(Victim("J", "Germany", 43, "asadsd.jpg"));
	Victim v = repoInMemory.findVictimByName("J");
	assert(v.getName() == "J"); //.compare("Jane") == 0);
	assert(v.getPlaceOfOrigin() == "Germany");//.compare("dasd") == 0);
	assert(v.getAge() == 43);

	//================ Test Iterator ========================
	repoInMemory.addVictim(Victim{ "As", "ASdasda", 343, "dsa.das" });
	repoInMemory.iterator();
	Victim v1{ "Jane", "dasd", 333, "asda" };
	Victim v2{ "J", "Germany", 43, "asadsd.jpg" }; 
	assert(repoInMemory.getCurrentVictim() == v1);
	repoInMemory.next();
	assert(repoInMemory.getCurrentVictim() == v2);
	repoInMemory.next();
	repoInMemory.next();
	assert(repoInMemory.isEmpty() == false);

	std::cout << "All repository in memory tests passed!" << std::endl;

}
void Tests::testRepoFile()
{
	FileRepo repoFile{ "tests.txt" };
	
	//================= Test Add ============================
	repoFile.addVictim(Victim{ "Janed", "Germany", 43, "asadsd.jpg" });
	repoFile.addVictim(Victim{ "Asd", "ASdasda", 343, "dsa.das" });
	assert(repoFile.getVictims().size() == 2);
	
	//================= Test Delete ============================
	repoFile.deleteVictim("Asd");
	assert(repoFile.getVictims().size() == 1);

	//================= Test Update ============================
	repoFile.updateVictim("Janed", "a", 1, "b");
	Victim v = repoFile.findVictimByName("Janed");
	Victim none = repoFile.findVictimByName("NuEste");
	assert(none == Victim{});
	assert(v.getName() == "Janed"); 
	assert(v.getPlaceOfOrigin() == "a");
	assert(v.getAge() == 1);
	assert(v.getPhoto() == "b");

	//================= Iterator Tests =========================

	repoFile.addVictim(Victim{ "As", "ASdasda", 343, "dsa.das" });
	repoFile.iterator();
	Victim v1{ "Janed", "a", 1, "b" };
	Victim v2{ "As", "ASdasda", 343, "dsa.das" };
	assert(repoFile.getCurrentVictim() == v1);
	repoFile.next();
	assert(repoFile.getCurrentVictim() == v2);
	assert(repoFile.isEmpty() == false);


	//clearing file...
	for (auto v : repoFile.getVictims()) {
		repoFile.deleteVictim(v.getName());
	}

	std::cout << "All repository file tests passed!" << std::endl;

}

void Tests::testRepoFile_invalidNameFile()
{
	FileRepo fileRepo{ "" };
	try {
		fileRepo.addVictim(Victim{ "asd", "asd", 3, "Asd" });}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.deleteVictim("asd");}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.updateVictim("sad", "asd", 3, "sada");}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.findVictimByName("asd");}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.getVictims();}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.getCurrentVictim();}
	catch (std::exception&) {
		assert(true);}
	try {
		fileRepo.iterator();}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.next();}
	catch (std::exception&) {
		assert(true);
	}
	try {
		fileRepo.isEmpty();}
	catch (std::exception&) {
		assert(true);
	}
}

void Tests::testDomain()
{
	Victim victim{ "Mary Jane", "Los Angeles", 33, "d.jpg" };
	assert(victim.getName() == "Mary Jane");
	assert(victim.getPlaceOfOrigin() == "Los Angeles");
	assert(victim.getAge() == 33);
	assert(victim.getPhoto() == "d.jpg");
	victim.setPlaceOfBirth("Romania");
	victim.setAge(55);
	victim.setPhoto("ds.jpg");
	assert(victim.getPlaceOfOrigin() == "Romania");
	assert(victim.getAge() == 55);
	assert(victim.getPhoto() == "ds.jpg");

	Victim victim1{ "M", "L", 3, "d" };
	assert(victim1 != victim);
	std::string toString = victim1.toString();
	assert(toString == "Name: M || Place of birth: L || Age: 3 || Photo: d");
	std::cout << "All domain tests past" << std::endl;
}


void Tests::testServiceAllTests()
{	
	testAddVictim_validElement_Succes();
	testAddVictim_EmptyName();
	testAddVictim_EmptyPlaceOfOrigin();
	testAddVictim_NegativeAge();
	testAddVictim_EmptyPhoto();
	testAddVictim_AlreadyAdded();

	testUpdateVictim_validElement_Succes();
	testUpdateVictim_InexitentName();
	testUpdateVictim_InvalidInputName();

	testDeleteVictim_validElement_Succes();
	testDeleteVictim_InexitentName();
	testDeleteVictim_InvalidInputName();

	testIteratorService();
	testNextIteratorService();
	
	
	std::cout << "All Service tests passed" << std::endl;

}

void Tests::testAddVictim_validElement_Succes()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	assert(service.getAllVictimsInRepo().size() == 1);
}

void Tests::testAddVictim_EmptyName()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };
	try { service.addVictimToRepository("", "Ro", 55, "a"); }
	catch (std::exception&)
	{
		assert(true);
	}
}

void Tests::testAddVictim_EmptyPlaceOfOrigin()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };


	try { service.addVictimToRepository("Dana", "", 55, "a"); }
	catch (std::exception&)
	{
		assert(true);
	}
}

void Tests::testAddVictim_NegativeAge()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	try { service.addVictimToRepository("Dana", "Ro", -55, "a"); }
	catch (std::exception&) {
		assert(true);
	}
}

void Tests::testAddVictim_EmptyPhoto()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	try { service.addVictimToRepository("Dana", "Ro", 55, ""); }
	catch (std::exception&) {
		assert(true);
	}
}

void Tests::testAddVictim_AlreadyAdded()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "s");
	try { service.addVictimToRepository("Dana", "Ro", 55, "s"); }
	catch (std::exception&) {
		assert(true);
	}

}

void Tests::testUpdateVictim_validElement_Succes()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	service.updateVictimFromRepo("Dana", "a", 66, "b");

	assert(service.getAllVictimsInRepo()[0].getAge() == 66);
	
}

void Tests::testUpdateVictim_InexitentName()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	try { service.updateVictimFromRepo("c", "s", 334, "d"); }
	catch (std::exception&)
	{
		assert(true);
	}
}

void Tests::testUpdateVictim_InvalidInputName()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	try { service.updateVictimFromRepo("", "s", 334, "d"); }
	catch (std::exception&)
	{
		assert(true);
	}
}

void Tests::testDeleteVictim_validElement_Succes()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	service.deleteVictimFromRepo("Dana");

	assert(service.getAllVictimsInRepo().size() == 0);
}

void Tests::testDeleteVictim_InexitentName()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	try { service.deleteVictimFromRepo("d"); }
	catch (std::exception&)
	{
		assert(true);
	}
}

void Tests::testDeleteVictim_InvalidInputName()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("Dana", "Ro", 55, "a");
	try { service.deleteVictimFromRepo(""); }
	catch (std::exception&)
	{
		assert(true);
	}
}

void Tests::testIteratorService()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("a", "a", 123, "d");
	service.iterator();
	Victim v = service.getCurrentFromIterator();
	assert(v.getAge() == 123);
	
}

void Tests::testNextIteratorService()
{
	Repository repo{};
	TransferListCSV list{ "CSV_TEST.txt" };
	Service service{ repo, list };

	service.addVictimToRepository("a", "a", 123, "d");
	service.iterator();
	service.next();
	Victim v = service.getCurrentFromIterator();
	assert(v.getAge() == 123);

}


