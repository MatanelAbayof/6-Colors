#pragma once
//---- include section ------
#include <string>
#include <mutex>

//---- using section --------
using std::string;

// define log just at debug mode
#if _DEBUG
#define LOG(x) Logger::getInterface().log(x)
#else
#define LOG(x) 
#endif


/*
 * Logger class.
 * this is Singleton design pattern
 * this is synchronized class - can used from many threads
 */
class Logger
{
public:
	// get interface
	static Logger& getInterface();
	// add new log (cout with mutex for multi-threads)
	void log(string message);
private:
	// constructor
	Logger() = default;
	// mutex
	mutable std::mutex m_mutex;
	// disable copy
	Logger& operator=(const Logger&) = delete;
	Logger(const Logger&) = delete;
};
