//---- include section -----------------
#include "NetworkException.h"

NetworkException::NetworkException(const std::string& errorMessage)
	: m_errorMessage(errorMessage)
{}

const char* NetworkException::what() const noexcept
{
	return m_errorMessage.c_str();
}
