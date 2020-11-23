#pragma once
#include "VirtualRepo.h"
#include "Exceptions.h"
#include <string>
class FileRepo : public RepoInterface
{private:
	std::string filename;
	int current = 0;

public:
	FileRepo(std::string filename);
	int addVictim(const Victim& victim) override;
	int deleteVictim(const std::string& name) override;
	int updateVictim(const std::string& name, const std::string& newPlaceOfOrigin, const int newAge, const std::string& newPhoto) override;
	Victim findVictimByName(const std::string& name) override;
	std::vector<Victim> getVictims() const override;
	
	void iterator() override { current = 0; };
	Victim getCurrentVictim() override;
	void next() override;
	bool isEmpty() override;

};

