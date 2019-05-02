//---- include section -----------------
#include "LoadResourceException.h"

GUI::LoadResourceException::LoadResourceException(const std::string& errorMessage) : m_errorMessage(errorMessage)
{}

const char* GUI::LoadResourceException::what() const noexcept
{
	return m_errorMessage.c_str();
}
