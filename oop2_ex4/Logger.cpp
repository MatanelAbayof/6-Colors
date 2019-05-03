//---- include section ------
#include "Logger.h"
#include <iostream>

Logger& Logger::getInterface()
{
	static Logger logger;
	return logger;
}

void Logger::log(string message)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::cout << message << std::endl;
}
