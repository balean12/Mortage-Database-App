#pragma once
#include "Victim.h"
#include <vector>
#include "Observer.h"
class TransferInterface : public Observable
{
protected:
	std::string filename;
public:
	TransferInterface(std::string filename) : filename{ filename } {};
	virtual int addToTransferList(const Victim& victim) = 0;
	virtual int deleteFromTransferList(const Victim& victim) = 0;
	virtual void getAll() = 0;
	virtual std::vector<Victim> getAllVector() = 0;
};