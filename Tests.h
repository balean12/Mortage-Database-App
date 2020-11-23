#pragma once
#include "VirtualRepo.h"
#include "Service.h"
#include "Victim.h"
#include <assert.h>
class Tests
{
public:
	void allTests();
private:

	//=============== Test Repository =================
	void testRepoInMemory();
	void testRepoFile();
	void testRepoFile_invalidNameFile();
	
	//=============== Test Domain =====================
	void testDomain();
	
	//=============== Test Service ====================
	void testServiceAllTests();
	void testAddVictim_validElement_Succes();
	void testAddVictim_EmptyName();
	void testAddVictim_EmptyPlaceOfOrigin();
	void testAddVictim_NegativeAge();
	void testAddVictim_EmptyPhoto();
	void testAddVictim_AlreadyAdded();

	void testUpdateVictim_validElement_Succes();
	void testUpdateVictim_InexitentName();
	void testUpdateVictim_InvalidInputName();

	void testDeleteVictim_validElement_Succes();
	void testDeleteVictim_InexitentName();
	void testDeleteVictim_InvalidInputName();

	void testIteratorService();
	void testNextIteratorService();
};