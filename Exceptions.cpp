#include "Exceptions.h"

ValidatorException::ValidatorException(std::string message)
{
	this->message = this->message + message;
}

const char* ValidatorException::what() const noexcept
{
	return this->message.c_str();
}

ServiceException::ServiceException(std::string message)
{
	this->message = this->message + message;
}

const char* ServiceException::what() const noexcept
{
	return this->message.c_str();
}

RepositoryException::RepositoryException(std::string message)
{
	this->message = this->message + message;
}

const char* RepositoryException::what() const noexcept
{
	return this->message.c_str();
}

TransferListException::TransferListException(std::string message)
{
	this->message = this->message + message;
}

const char* TransferListException::what() const noexcept
{
	return this->message.c_str();
}

