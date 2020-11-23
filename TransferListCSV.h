#pragma once
#include <vector>
#include <string>
#include "Victim.h"
#include "TransferListInterface.h"
class TransferListCSV : public TransferInterface
{

public:
	TransferListCSV(std::string filename) :TransferInterface{ filename } {};
	int addToTransferList(const Victim& victim) override;
	int deleteFromTransferList(const Victim& victim) override;
	void getAll() override;
	std::vector<Victim> getAllVector() override;
	
};