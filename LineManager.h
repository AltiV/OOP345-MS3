// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, December 1st, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef MS3_LINEMANAGER_H
#define MS3_LINEMANAGER_H

#include <deque>
#include <string>
#include <vector>

#include "Task.h"
#include "CustomerOrder.h"

class LineManager {
	std::vector<Task*> AssemblyLine;		// A container containing all the references of the Task objects on the assembly line
	std::deque<CustomerOrder> ToBeFilled;	// A queue of customer orders to be filled
	std::deque<CustomerOrder> Completed;	// A queue of customer orders completed
	unsigned int m_cntCustomerOrder;		// The number of CustomerOrder objects the assembly line started with.
	unsigned int aLineStart;				// Custom variable to hold the index of the first Task of the AssemblyLine
	unsigned int aLineEnd;					// Custom variable to hold the index of the last Task of the AssemblyLine
public:
	LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);	// Custom Constructor that moves and copies objects to appropriate locations
	bool run(std::ostream&);															// Performs one cycle of operations on the assembly line that moves and loops objects
	void displayCompleted(std::ostream&) const;											// Displays all the orders that were completed
	void validateTasks() const;															// Validates each task on the assembly line
};

#endif