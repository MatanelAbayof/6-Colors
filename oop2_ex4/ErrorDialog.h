#pragma once
//---- include section ------
#include "AlertDialog.h"
#include <string>

//---- using section --------
using std::string;

namespace GUI {
/*
 * ErrorDialog class
 */
class ErrorDialog :
	public AlertDialog
{
public:
	// show error dialog
	static void show(const string& errorMessage);
	// convert to string
	virtual string toString() const override;
private:
	// constructor
	explicit ErrorDialog(sf::RenderWindow& window, const string& errorMessage);
	// init components
	void initComponents();
	// disable show of base class
	using AlertDialog::show;
};
}
