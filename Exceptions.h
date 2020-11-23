#pragma once
#include <string>

class ValidatorException : public std::exception
{
private:
	std::string message = "ValidatorException: ";
public:
	ValidatorException(std::string message);
	const char* what() const noexcept override;
};


class ServiceException : public std::exception
{
private:
	std::string message = "ServiceException: ";
public:
	ServiceException(std::string message);
	const char* what() const noexcept override;
};

class RepositoryException :public std::exception
{
private:
	std::string message = "RepositoryException: ";
public:
	RepositoryException(std::string message);
	const char* what() const noexcept override;
};

class TransferListException :public std::exception
{
private:
	std::string message = "TransferListException: ";
public:
	TransferListException(std::string message);
	const char* what() const noexcept override;
};