// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Sunday, November 25th, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef MS1_CUSTOMERORDER_H
#define MS1_CUSTOMERORDER_H

#include <string>

#include "Item.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name;			// Name of customer
	std::string m_product;		// Name of the product being assembled
	unsigned int m_cntItem;		// Count of the number of items for the customer's order
	ItemInfo** m_lstItem;		// Dynamically allocated array of pointers to be managed
	static size_t m_widthField;	// Maximum width of a field, used for display purposes
public:
	CustomerOrder();											// Default Constructor
	CustomerOrder(std::string&);								// Constructor taking record from input file
	CustomerOrder(const CustomerOrder&);						// No copy operations allowed for this object (will throw an exception for constructor)
	CustomerOrder& operator=(const CustomerOrder&) = delete;	// No copy operations allowed for this object
	CustomerOrder(CustomerOrder&&) noexcept;					// Move Constructor
	CustomerOrder& operator=(CustomerOrder&&);					// Move Assignment Operator
	~CustomerOrder();											// Destructor
	bool getItemFillState(std::string) const;					// Returns ItemInfo::m_fillState of item specified as parameter
	bool getOrderFillState() const;								// Returns if all items in order have been filled
	void fillItem(Item& item, std::ostream& os);				// Fills item in current order that corresponds to item passed into function
	void display(std::ostream&) const;							// Displays state of current object
};

#endif