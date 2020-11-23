#pragma once
#include "TransferListInterface.h"
#include "Victim.h"

class TransferHTML : public TransferInterface
{
private:
	std::vector<Victim> savedVictims;
public:
	TransferHTML(std::string filename):TransferInterface{ filename } {};
	int addToTransferList(const Victim& victim) override;
	int deleteFromTransferList(const Victim& victim) override;
	void getAll() override;
	std::vector<Victim> getAllVector() override;
};