// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, December 1st, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "LineManager.h"
#include "Utilities.h"

// Command Line: ms3 Inventory1.dat Inventory2.dat CustomerOrders.dat AssemblyLine.dat

// Custom Constructor that moves and copies objects to appropriate locations
LineManager::LineManager(const std::string& record, std::vector<Task*>& tasks, std::vector<CustomerOrder>& customerOrders) {
	try {
		// Create Utilities object to use extract function
		Utilities util;

		// Create position variable to track which part of string to read from
		size_t pos = 0;

		// Create temporary vector to hold the values extracted from record
		std::vector<std::string> tempVec;

		// Create boolean to keep track of when record is finished reading
		bool notDone = true;

		// Create an ifstream variable to hold the file
		std::ifstream file(record);

		if (!file)
			throw std::string("Unable to open [") + record + "] file.";

		// Create a string variable to hold lines being fed from the file to be pushed into the temporary vector
		std::string collection;

		// Read through the file
		while (!file.eof())
		{
			// Get a line
			std::getline(file, collection);

			// Chop it up and insert it into slots within the temporary vector, adjusting the position to read the string as necessary
			while (notDone) {
				tempVec.push_back(util.extractToken(collection, pos, notDone));
				pos += tempVec[tempVec.size() - 1].length() + 1;
			}
			// Remove the last item that gets fed into the temporary vector because it's just whitespace signifying end of line
			tempVec.pop_back();
			
			// Reset string tracking variable
			pos = 0;

			// Reset the notDone variable for the the extractToken to work again on the next iteration
			notDone = true;
		}

		// File is finished being worked with and can now be closed
		file.close();

		// Determine the index of the first and last items in the Assembly Line for the Task vector
		auto firstItem = std::find_if(tasks.begin(), tasks.end(), [=](Task* it) {return it->getName() == tempVec[0];});

		this->aLineStart = (unsigned int)std::distance(tasks.begin(), firstItem);

		auto lastItem = std::find_if(tasks.begin(), tasks.end(), [=](Task* it) {return it->getName() == tempVec[tempVec.size() - 1];});

		this->aLineEnd = (unsigned int)std::distance(tasks.begin(), lastItem);

		// Read through the vector of Task pointers, and determine next task based on given file
		for (Task* iter : tasks) {

			// Find the last string in the file of item names that matches the task's name
			auto result = std::find_if(tempVec.rbegin(), tempVec.rend(),
				[=](std::string itemName) { return itemName == iter->getName(); });

			// Get the position of that name in the string vector
			size_t index = std::distance(result, tempVec.rend());

			// If this is not the last item (which means it's the end of the line), set the item following it in the Task vector to be the next task
			// This sets up the m_pNextTask references, and handles "Linking each Task object together to form the assembly line"
			if (index != tempVec.size()) {
				auto nextTask = std::find_if(tasks.begin(), tasks.end(),
					[=](Task* targetTask) { return targetTask->getName() == tempVec[index + 1]; });

				iter->setNextTask(**nextTask);
			}
		}

		// Store number of customerOrder objects that are started with
		this->m_cntCustomerOrder = (unsigned int)customerOrders.size();

		// Move all the CustomerOrder objects onto the front of the ToBeFilled queue
		for (size_t num = 0; num < customerOrders.size(); ++num) {
			this->ToBeFilled.push_front(std::move(customerOrders[num]));
		}

		// Remove all the orders from the original vector, as they have been filed to be filled
		customerOrders.erase(customerOrders.begin(), customerOrders.end());

		// Copy all the Task objects into the AssemblyLine container
		this->AssemblyLine = tasks;
	}
	catch (...) {
		std::cout << "An error has occured in the LineManager three-argument constructor." << std::endl;
	}
}

// Performs one cycle of operations on the assembly line that moves and loops objects
bool LineManager::run(std::ostream& os) {

	// Initialize customer orders being filled to true, which will be falsified if any items are still remaining
	bool filled = true;

	if (!this->ToBeFilled.empty()) {

		// Move the last CustomerOrder object in the ToBeFilled queue into the front of the AssemblyLine vector's m_orders queue
		*this->AssemblyLine[this->aLineStart] += std::move(this->ToBeFilled.back());

		// Remove that CustomerOrder object from the ToBeFilled queue as it has been moved
		this->ToBeFilled.pop_back();
	}

	// "Loop through all tasks on the assembly line and run one cycle of the task’s process"
	for (Task* task : this->AssemblyLine) {
		task->runProcess(std::cout);
	}

	// Create a temporary CustomerOrder object to hold the information from tasks reaching the end of the assembly line, to be fed into Completed queue
	CustomerOrder transferOrder;

	// Once the order has reached the end, it should be completed and can be pushed into the respective queue
	if (this->AssemblyLine[this->aLineEnd]->getCompleted(transferOrder)) {
		this->Completed.push_back(std::move(transferOrder));
	}

	// "Loop through all tasks on the assembly line and move the CustomerOrder objects down the line."
	// If there is any task that is moved, that means the assembly line is still working and all of the orders are not filled yet
	for (Task* task : this->AssemblyLine) {
		if (task->moveTask()) {
			filled = false;
		}
	}

	// If the return value is false, that means this function will continue running in the main program
	return filled;
}

// Displays all the orders that were completed
void LineManager::displayCompleted(std::ostream& os) const {
	for (size_t num = 0; num < this->Completed.size(); ++num) {
		this->Completed[num].display(std::cout);
	}
}

// Validates each task on the assembly line
void LineManager::validateTasks() const {
	for (Task* task : this->AssemblyLine) {
		task->validate(std::cout);
	}
}