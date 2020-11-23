#include "Victim.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Victim::Victim() :name(""), placeOfOrigin(""), age(0), photo("") {}

Victim::Victim(const std::string& name, const std::string& placeOfOrigin, int age, const std::string& photo)
{
	this->name = name;
	this->placeOfOrigin = placeOfOrigin;
	this->age = age;
	this->photo = photo;
}

bool Victim::operator==(const Victim& v)
{
	return(this->name == v.name && this->placeOfOrigin == v.placeOfOrigin && this->age == v.age && this->photo == v.photo);
}

bool Victim::operator!=(const Victim& v)
{
	return(this->name != v.name);
}

void Victim::setName(const std::string& newName)
{
	this->name = newName;
}

void Victim::setPlaceOfBirth(const std::string& newPlaceOfBirth)
{
	this->placeOfOrigin = newPlaceOfBirth;
}


void Victim::setAge(const int newAge)
{
	this->age = newAge;
}

void Victim::setPhoto(const std::string& newPhoto)
{
	this->photo = newPhoto;
}

std::string Victim::toString()
{
	return  "Name: " + this->getName() + " || Place of birth: " + this->getPlaceOfOrigin() + " || Age: " + std::to_string(this->getAge()) + " || Photo: " + this->getPhoto();
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	vector<string> result;
	stringstream strstream(str);
	string token;
	while (getline(strstream, token, delimiter))
		result.push_back(token);

	return result;
}
std::istream& operator>>(std::istream& stream, Victim& v)
{
	string line;
	getline(stream, line);
	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 4)
		return stream;
	v.name = tokens[0];
	v.placeOfOrigin = tokens[1];
	v.age = stoi(tokens[2]);
	v.photo = tokens[3];
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Victim& v)
{
	stream << v.name << "," << v.placeOfOrigin << "," << v.age << "," << v.photo;
	return stream;
}
