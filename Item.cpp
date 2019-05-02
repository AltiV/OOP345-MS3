// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, November 10th, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Utilities.h"
#include "Item.h"

#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>

// Initialize static variable m_widthField
size_t Item::m_widthField;

// Set maximum characters to be displayed for serial number as 6 for now
size_t Item::m_widthSerial = 6;

// One-argument constructor
Item::Item(const std::string record)  {
	// Wrap constructor code in a try-catch statement in case a record is provided that throws an error
	try {
		// Create Utilities object to use extract function
		Utilities util;

		// Create position variable to track which part of string to read from
		size_t pos = 0;

		// Create temporary vector to hold the values extracted from record
		std::vector<std::string> tempVec;

		// Create boolean to keep track of when record is finished reading
		bool notDone = true;

		while (notDone) {
			tempVec.push_back(util.extractToken(record, pos, notDone));
			pos += tempVec[tempVec.size() - 1].length() + 1;
		}

		// Take the four strings extracted from record and equate them to the relevant variables (any extraneous information should not exist)
		this->m_name = tempVec[0];
		this->m_serialNumber = stoi(tempVec[1]);
		this->m_quantity = stoi(tempVec[2]);
		this->m_description = tempVec[3];

		// Set width field to maximum of current and the utilities value
		Item::m_widthField = std::max(Item::m_widthField, util.getFieldWidth());
	}
	// Error handling for two delimiters with nothing in between
	catch (std::string err) {
		std::cout << err << std::endl;
	}
	// Default catch statement
	catch (...) {
		std::cout << "An unknown error has occured." << std::endl;
	}
}

// Return name of current Item object
const std::string& Item::getName() const {
	return this->m_name;
}

// Return description of current Item object
const std::string& Item::getDescription() const {
	return this->m_description;
}

// Return next serial number to be used on assembly line and increments number
const unsigned int Item::getSerialNumber() {
	return this->m_serialNumber++;
}

// Get remaining quantity of current Item object
const unsigned int Item::getQuantity() {
	return this->m_quantity;
}

// Subtracts one from available quantity, but not below 0
void Item::updateQuantity() {
	this->m_quantity = std::max(this->m_quantity - 1, 0);
}

// Inserts content of current object into first parameter
void Item::display(std::ostream& os, bool full) const {
	os << std::left << std::setw(this->m_widthField) << this->getName() << " [" << std::right << std::setw(this->m_widthSerial) << std::setfill('0') << m_serialNumber << std::setfill(' ') << "]";
	// If full is set to true, include the quantity and description information
	if (full) {
		os << " Quantity: " << std::left << std::setw(this->m_widthField) << m_quantity << " Description: " << this->getDescription();
	}
	os << std::endl;
}