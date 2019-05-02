// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, December 1st, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iostream>

#include "Task.h"

// Custom Constructor
Task::Task(const std::string& record) : Item(record), m_pNextTask{ nullptr } {}

// Runs a single cycle of the assembly line for the current task
void Task::runProcess(std::ostream& os) {
	// If the m_orders queue still has customer orders in it, and the back order is not fully filled, fill that last order with the item
	if (!this->m_orders.empty() && !this->m_orders.back().getOrderFillState()) {
		this->m_orders.back().fillItem(*this, os);
	}
}

// Moves the last CustomerOrder in the queue to the next task on the assembly line
bool Task::moveTask() {

	bool queueStatus = false;

	// Check if the m_orders queue is non-empty; if so, the function will return true
	if (!this->m_orders.empty()) {

		// Check if the last order in the queue has a filled state to move it to the next task on the assembly line if so
		if (this->m_orders.back().getItemFillState(this->getName()) && m_pNextTask) {
			*this->m_pNextTask += std::move(this->m_orders.back());
			this->m_orders.pop_back();
		}
		queueStatus = true;
	}

	return queueStatus;
}

// Stores the provided Task object’s reference into the m_pNextTask pointer
void Task::setNextTask(Task& task) {
	this->m_pNextTask = &task;
}

// Removes the last CustomerOrder from the queue and places it in the parameter
bool Task::getCompleted(CustomerOrder& customerOrder) {
	bool queueStatus = false;

	// Check if queue is non-empty to return true
	if (!this->m_orders.empty()) {

		// Check if the last item in the queue has a filled state to move it to the given parameter
		if (this->m_orders.back().getItemFillState(this->getName())) {
			customerOrder = std::move(this->m_orders.back());
			this->m_orders.pop_back();
		}
		queueStatus = true;
	}

	return queueStatus;
}

// Writes the name of the Item this Task is responsible for into the parameter
void Task::validate(std::ostream& os) {
	os << this->getName();
	os << " --> ";

	// If there is a next task, include its name, otherwise, end the line
	this->m_pNextTask != nullptr ? os << this->m_pNextTask->getName() : os << "END OF LINE";
	os << std::endl;
}

// Moves the given parameter onto the front of the m_orders queue
Task& Task::operator+=(CustomerOrder&& customerOrder) {
	this->m_orders.push_front(std::move(customerOrder));

	return *this;
}