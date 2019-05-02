#pragma once
//---- include section ------
#include <exception>
#include <string>

namespace GUI {
/*
 * LoadResourceException class
 */
class LoadResourceException : public std::exception
{
public:
	// constructor
	explicit LoadResourceException(const std::string& errorMessage = "");
	// message of exception
	virtual const char* what() const noexcept override;
private:
	// error message
	std::string m_errorMessage;
};
}
