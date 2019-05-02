// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, November 10th, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef MS1_ITEM_H
#define MS1_ITEM_H

#include <string>

class Item {
	// Name of item
	std::string m_name;

	// Description of item
	std::string m_description;

	// Next serial number to be assigned on assembly line
	unsigned int m_serialNumber;

	// Number of current items left in stock
	int m_quantity;

	// Maximum characters to be displayed for field
	static size_t m_widthField;

	// Maximum characters to be displayed for serial number
	static size_t m_widthSerial;
public:
	// One-argument constructor
	Item(const std::string);

	// Return name of current Item object
	const std::string& getName() const;

	// Return description of current Item object
	const std::string& getDescription() const;

	// Return next serial number to be used on assembly line and increments number
	const unsigned int getSerialNumber();

	// Get remaining quantity of current Item object
	const unsigned int getQuantity();

	// Subtracts one from available quantity, but not below 0
	void updateQuantity();

	// Inserts content of current object into first parameter
	void display(std::ostream& os, bool full) const;
};

#endif