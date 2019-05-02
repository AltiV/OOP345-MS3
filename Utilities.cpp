// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, November 10th, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Utilities.h"

// Initialize static m_delimiter variable as nothing
char Utilities::m_delimiter;

// Sets field width of current object to value of given parameter
void Utilities::setFieldWidth(size_t width) {
	this->m_widthField = width;
}

// Return field width of current object
size_t Utilities::getFieldWidth() const {
	return this->m_widthField;
}

// Extract token from first parameter using delimiter
const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	// Instantiate a temporary string variable to hold required information
	std::string line;

	if (str.length() > next_pos) {
		// Ensure that the function that calls this will continue running
		more = true;

		// Get the location of the delimiter for provided fragment of string
		size_t delimPos = str.substr(next_pos).find(this->getDelimiter());

		// Extract token
		line = str.substr(next_pos, delimPos);

		// If nothing was extracted, that means there were two delimiters present with nothing in between
		if (line.length() == 0) {
			throw "No token found between two delimiters.";
		}

		// Set the field width to the maximum of current value and token length, but NOT if it's the last item in the record...
		if (line.length() > this->getFieldWidth() && delimPos != std::string::npos) {
			this->setFieldWidth(line.length());
		}
	}
	// Otherwise, end of record has been reached
	else {
		more = false;
	}
	
	// Regardless, return the line
	return line;
}

// Set delimiter for class to character received
void Utilities::setDelimiter(const char delimiter) {
	m_delimiter = delimiter;
}

// Return delimiter character of current object
const char Utilities::getDelimiter() const {
	return m_delimiter;
}
