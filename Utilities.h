// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, November 10th, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef MS1_UTILITIES_H
#define MS1_UTILITIES_H

#include <string>

class Utilities {
	// Specifies length of token extracted; default value of 1
	size_t m_widthField = 1;

	// Shared delimiter which separates tokens from given string
	static char m_delimiter;
public:
	// Sets field width of current object to value of given parameter
	void setFieldWidth(size_t);

	// Return field width of current object
	size_t getFieldWidth() const;

	// Extract token from first parameter using delimiter
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

	// Set delimiter for class to character received
	static void setDelimiter(const char);

	// Return delimiter character of current object
	const char getDelimiter() const;
};

#endif