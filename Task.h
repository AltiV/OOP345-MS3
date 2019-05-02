// Name:				Alan Vuong
// Seneca Student ID:	149004178
// Seneca email:		avuong19@myseneca.ca
// Date of completion:	Saturday, December 1st, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef MS3_TASK_H
#define MS3_TASK_H

#include <deque>
#include <string>

#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
	std::deque<CustomerOrder> m_orders; // Double ended queue with new CustomerOrders being filled before exiting
	Task* m_pNextTask;					// Pointer to the next task on the assembly line
public:
	Task(const std::string&);				// Custom Constructor
	Task(const Task&) = delete;				// No copy or move operators permitted
	Task& operator=(const Task&) = delete;	// No copy or move operators permitted
	Task(Task&&) = delete;					// No copy or move operators permitted
	Task& operator=(Task&&) = delete;		// No copy or move operators permitted
	void runProcess(std::ostream&);			// Runs a single cycle of the assembly line for the current task
	bool moveTask();						// Moves the last CustomerOrder in the queue to the next task on the assembly line
	void setNextTask(Task&);				// Stores the provided Task object’s reference into the m_pNextTask pointer
	bool getCompleted(CustomerOrder&);		// Removes the last CustomerOrder from the queue and places it in the parameter
	void validate(std::ostream&);			// Writes the name of the Item this Task is responsible for into the parameter
	Task& operator+=(CustomerOrder&&);		// Moves the parameter onto the front of the CustomerOrder queue
};

#endif


//A Task object manages a single Item on the assembly line.
//
//Task inherits from class Item and contains the following additional information :
//
//m_orders – is a double ended queue with new CustomerOrders coming in one side and exiting out the other once filled.
//m_pNextTask – a pointer to the next task on the assembly line
//
//The member functions of the Task class include :
//
//	a custom constructor — upon instantiation, a Task object receives a reference to an unmodifiable std::string.This string contains a single record(one line) that has been retrieved from the input file specified by the user to be used for Item instantiation.
//	this constructor will also set the m_pNextTask to a safe state.
//	A Task object represents a single location on the assembly line for filling items into customer orders.Therefore, a Task object cannot be copied or moved.You must make sure this capability has been deleted from your Task definition.
//	void runProcess(std::ostream&) – runs a single cycle of the assembly line for the current task.
//	If there are CustomerOrders in the queue, it will verify the fill status of the last CustomerOrder and fill it if the order contains the Item specified by the current Task.
//	bool moveTask() – moves the last CustomerOrder in the queue to the next task on the assembly line if the orders fill state for the current Item is true.Otherwise, the CustomerOrder should remain in the queue for the next processing cycle.If the queue is empty, return false.
//	void setNextTask(Task&) – stores the provided Task object’s reference into the m_pNextTask pointer.
//	bool getCompleted(CustomerOrder&) – Removes the last CustomerOrder from the queue, places it in the parameter and returns true.If the CustomerOrder queue is empty, return false.
//	void validate(std::ostream&) – writes the name of the Item this Task is responsible for into the parameter : ITEM_NAME-- > NEXT_ITEM_NAME
//	if m_pNextTask does not exist it writes : ITEM_NAME-- > END OF LINE.
//		the messages are terminated with an endline
//		Task& operator+=(CustomerOrder&&) – Moves the parameter onto the front of the CustomerOrder queue.
//