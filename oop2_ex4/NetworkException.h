#pragma once
//---- include section ------
#include <exception>
#include <string>

/*
 * NetworkException class
 */
class NetworkException : public std::exception
{
public:
	// constructor
	explicit NetworkException(const std::string& errorMessage = "");
	// message of exception
	virtual const char* what() const noexcept override;
private:
	// error message
	std::string m_errorMessage;
};



