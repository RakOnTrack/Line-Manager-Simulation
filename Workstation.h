// Name: Eric Rak
// Seneca Student ID: 180211211
// Seneca email: erak@myseneca.ca
// Date of completion: Mar 25th 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <string>

#include <iomanip>
#include <cstring>
#include <string>
#include <cctype>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{


	CustomerOrder* g_pending{};    // holds the orders to be placed onto the assembly line at the first station.
	CustomerOrder* g_completed{};  // holds the orders that have been removed from the last station and have been completely filled.
	CustomerOrder* g_incomplete{}; // holds the orders that have been removed from the last station and could not be filled
	class Workstation : public Station
	{
		// The Workstation module consists of three double-ended queues of CustomerOrder and the Workstation class.
		//   The queues (global variables) hold the orders at either end of the assembly line:
		//  completely.
		// Each queue is accessible outside this module's translation unit.

		// The Workstation class defines the structure of an active station on the assembly line and contains all
		//  the functionality for filling customer orders with station items. Each Workstation is-a-kind-of Station.
		//   A Workstation object manages order processing for a single Item on the assembly line. Since a Workstation
		//   object represents a single location on the assembly line for filling customer orders with items, the
		//   object cannot be copied or moved. Make sure that this capability is deleted in your definition of the
		//   Workstation class.

		// The Workstation class includes the following additional information:

		// Instance Variables

		// m_orders – is a double-ended-queue with CustomerOrders entering the back and exiting the front. These
		//  are orders that have been placed on this station to receive service (or already received service).
		std::deque<CustomerOrder> m_orders{};
		// m_pNextStation – a pointer to the next Workstation on the assembly line.
		// Member Functions
		Station* m_pNextStation{};

	public:
		// a custom 1-argument constructor -- receives a reference to an unmodifiable reference to std::string
		//   and passes it to the Station base class.
		Workstation(const char* str) : Station(str) {};

		// void fill(std::ostream& os) – this modifier fills the order at the front of the queue if there are
		//  CustomerOrders in the queue; otherwise, does nothing.
		void fill(std::ostream& os);
		// bool attemptToMoveOrder() – attempts to move the order order at the front of the queue to the next
		//  station in the assembly line:
		bool attemptToMoveOrder();
		// if the order requires no more service at this station or cannot be filled (not enough inventory),
		//   move it to the next station; otherwise do nothing
		// if there is no next station in the assembly line, then the order is moved into g_completed or
		//   g_incomplete queue
		// if an order has been moved, return true; false otherwise.
		// void setNextStation(Workstation* station) – this modifier stores the address of the referenced
		//   Workstation object in the pointer to the m_pNextStation. Parameter defaults to nullptr.
		void setNextStation(Workstation* station = nullptr);

		// Workstation* getNextStation() const – this query returns the address of next Workstation
		Workstation* getNextStation() const;

		// void display(std::ostream& os) const – this query inserts the name of the Item for which the
		//  current object is responsible into stream os following the format: ITEM_NAME --> NEXT_ITEM_NAME
		void display(std::ostream& os) const;

		// if the current object is the last Workstation in the assembly line this query inserts: ITEM_NAME
		//  --> End of Line.
		// in either case, the message is terminated with \n



		// Workstation& operator+=(CustomerOrder&& newOrder) – moves the CustomerOrder referenced in parameter
		//   newOrder to the back of the queue.
		Workstation& operator+=(CustomerOrder&& newOrder);
	};

}

#endif