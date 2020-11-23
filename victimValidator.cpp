#include "victimValidator.h"
#include "Exceptions.h"
using namespace std;
void VictimValidator::validateVictim(const Victim& victim)
{
	string errors;
	if (victim.getName() == "")
		errors += string("Empty name\n");
	if (victim.getPlaceOfOrigin() == "")
		errors += string("Empty place of origin\n");
	if (victim.getPhoto() == "")
		errors += string("Empty link\n");
	if (victim.getAge() < 1)
		errors += string("Invalid age ( <1 )!");
	if (errors.size() > 0)
		throw ValidatorException(errors);

}
