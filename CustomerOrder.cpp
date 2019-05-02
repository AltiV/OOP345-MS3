// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, December 1st, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>

#include "CustomerOrder.h"
#include "Utilities.h"

// Initialize static variable m_widthField
size_t CustomerOrder::m_widthField;

// Default Constructor
CustomerOrder::CustomerOrder() : m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_lstItem{ nullptr } {}

// Constructor taking record from input file
CustomerOrder::CustomerOrder(std::string& record) {
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

		// Take the two first strings extracted from record and equate them to the relevant variables
		this->m_name = tempVec[0];
		this->m_product = tempVec[1];

		// Determine tne number of items to be equal to the size of the temporary vector minus the name, product name, and end data
		this->m_cntItem = int(tempVec.size() - 3);

		// Set item list as a new array of ItemInfo pointers with m_cntItem elements
		this->m_lstItem = new ItemInfo*[this->m_cntItem];

		for (size_t item = 0; item < this->m_cntItem; ++item) {
			this->m_lstItem[item] = new ItemInfo(tempVec[item + 2]);
		}

		// Set width field to maximum of current and the utilities value
		CustomerOrder::m_widthField = std::max(CustomerOrder::m_widthField, util.getFieldWidth());

	}
	catch (...) {
		std::cout << "An error has occured in the one-argument constructor." << std::endl;
	}
}

// No copy operations allowed for this object (will throw an exception for constructor)
CustomerOrder::CustomerOrder(const CustomerOrder& co) {
	throw "This is not allowed.";
}

// Move Constructor
CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept : CustomerOrder() {
	*this = std::move(co);
}

// Move Assignment Operator
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) {
	if (this != &co)
	{
		delete[] this->m_lstItem;

		this->m_name = co.m_name;
		this->m_product = co.m_product;
		this->m_cntItem = co.m_cntItem;
		this->m_lstItem = co.m_lstItem;

		// Set fed object's values to uninitialized
		co.m_name = "";
		co.m_product = "";
		co.m_cntItem = 0;
		co.m_lstItem = nullptr;
	}

	return *this;
}

// Destructor
CustomerOrder::~CustomerOrder() {
	delete[] this->m_lstItem;
}

// Returns ItemInfo::m_fillState of item specified as parameter
bool CustomerOrder::getItemFillState(std::string item) const {
	// Start with the item filled state set as true
	bool filled = true;

	// Once the item is found, set the filled state to what it is labelled as and break out
	for (size_t i = 0; i < this->m_cntItem; i++)
	{
		if (item == this->m_lstItem[i]->m_itemName)
		{
			filled = this->m_lstItem[i]->m_fillState;

			//std::cout << "String from getItemFillState: " << filled << std::endl;

			if (!filled) {
				break;
			}
		}
	}

	return filled;
}

// Returns if all items in order have been filled
bool CustomerOrder::getOrderFillState() const {
	// Start with the item filled state set as true
	bool filled = true;

	// If any fillstate in the object is missing, immediately return false
	for (size_t i = 0; i < this->m_cntItem; i++)
	{
		if (!this->m_lstItem[i]->m_fillState)
		{
			filled = false;
			break;
		}
	}

	return filled;
}

// Fills item in current order that corresponds to item passed into function
void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	for (size_t i = 0; i < this->m_cntItem; i++) {
		if (item.getName() == this->m_lstItem[i]->m_itemName && !this->m_lstItem[i]->m_fillState) {
			if (item.getQuantity() > 0) {
				item.updateQuantity();
				this->m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				this->m_lstItem[i]->m_fillState = true;
				os << "Filled ";
			}
			else {
				os << "Unable to fill ";
			}
			os << this->m_name << ", " << this->m_product << "[" << this->m_lstItem[i]->m_itemName << "]" << std::endl;
		}
	}
}

// Displays state of current object
void CustomerOrder::display(std::ostream& os) const {
	os << this->m_name << " - " << this->m_product << std::endl;

	for (size_t item = 0; item < this->m_cntItem; ++item)
	{
		os << std::setfill('0') << "[" << std::right << std::setw(6) << this->m_lstItem[item]->m_serialNumber << "] ";
		os << std::setfill(' ') << std::left << std::setw(this->m_widthField);
		os << this->m_lstItem[item]->m_itemName << " - ";

		this->m_lstItem[item]->m_fillState ? os << "FILLED" : os << "MISSING";

		os << std::endl;
	}
}