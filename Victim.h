#pragma once
#include <iostream>
#include <string>
class Victim
{
private:
	std::string name;
	std::string placeOfOrigin;
	int age;
	std::string photo;
public:
	//default constructor for a victim
	Victim();

	//constructor with parameters
	Victim(const std::string& name, const std::string& placeOfOrigin, int age, const std::string& photo);

	//returns name of the victim
	std::string getName() const { return name; };
	//returns victim's place of origin
	std::string getPlaceOfOrigin() const { return placeOfOrigin; };
	//returns victim's age
	int getAge() const { return age; };
	//returns victim's phto
	std::string getPhoto() const { return photo; };
	bool operator==(const Victim& v);
	bool operator!=(const Victim& v);


	//setters
	void setName(const std::string& newName);
	void setPlaceOfBirth(const std::string& newPlaceOfBirth);
	void setAge(const int newAge);
	void setPhoto(const std::string& newPhoto);
	
	friend std::istream& operator>>(std::istream& stream, Victim& v);
	friend std::ostream& operator<<(std::ostream& stream, const Victim& v);
	//return a string with the Victim's data
	std::string toString();
};