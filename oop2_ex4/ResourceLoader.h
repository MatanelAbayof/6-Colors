#pragma once
//---- include section ------
#include <string>

//---- using section --------
using std::string;

namespace GUI {
/*
* ResourceLoader class.
*/
class ResourceLoader
{
public:
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	ResourceLoader() = default;
private:
	// disable copy
	ResourceLoader& operator=(const ResourceLoader&) = delete;
	ResourceLoader(const ResourceLoader&) = delete;
};
}
