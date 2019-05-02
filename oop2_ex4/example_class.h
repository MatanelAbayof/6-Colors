#pragma once
//---- include section ------
#include <string>

//---- using section --------
using std::string;

/*
 * $$CLASS_NAME$$ class
 */
class ExampleClass
{
public:
	// constructor
	ExampleClass();
	// destructor
	~ExampleClass();
	// convert to string
	virtual string toString() const;
private:
	// TODO members here
};

