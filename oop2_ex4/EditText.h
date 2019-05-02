#pragma once
//---- include section ------
#include <string>
#include "TextView.h"

//---- using section --------
using std::string;

namespace GUI {
/*
 * EditText class
 */
class EditText :
	public TextView
{
public:
	// constructor
	explicit EditText(sf::RenderWindow& window, const string& text = "");
	// start record text
	void startRecordText() { m_recordText = true; }
	// stop record text
	void stopRecordText() { m_recordText = false; }
	// check if is record text
	bool isRecordText() const { return m_recordText; }
	// convert to string
	virtual string toString() const override;
protected:
	// record text
	bool m_recordText;
	// init
	void init();
};
}
