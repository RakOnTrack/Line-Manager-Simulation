// Name: Eric Rak
// Seneca Student ID: 180211211
// Seneca email: erak@myseneca.ca
// Date of completion: Mar 25th 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Workstation.h"

using namespace std;

namespace sdds
{

    // void fill(std::ostream& os) – this modifier fills the order at the front of the queue if there are
    //  CustomerOrders in the queue; otherwise, does nothing.
    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {

            m_orders.front().fillItem(*this, os);
        }
    }
    // bool attemptToMoveOrder() – attempts to move the order order at the front of the queue to the next
    //  station in the assembly line:
    bool Workstation::attemptToMoveOrder()
    {
        if (!m_orders.empty() && m_orders.front().isOrderFilled())
        {
            // if (m_pNextStation && m_pNextStation->acceptOrder(m_orders.front()))
            if (m_pNextStation)
            {
                m_orders.pop_front();
                return m_pNextStation == nullptr;
            }
        }
        return false;
    }
    // if the order requires no more service at this station or cannot be filled (not enough inventory),
    //   move it to the next station; otherwise do nothing
    // if there is no next station in the assembly line, then the order is moved into g_completed or
    //   g_incomplete queue
    // if an order has been moved, return true; false otherwise.
    // void setNextStation(Workstation* station) – this modifier stores the address of the referenced
    //   Workstation object in the pointer to the m_pNextStation. Parameter defaults to nullptr.
    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    // Workstation* getNextStation() const – this query returns the address of next Workstation
    Workstation *Workstation::getNextStation() const
    {
        return (Workstation *)m_pNextStation;
    }

    // void display(std::ostream& os) const – this query inserts the name of the Item for which the
    //  current object is responsible into stream os following the format: ITEM_NAME --> NEXT_ITEM_NAME
    void Workstation::display(std::ostream &os) const
    {

        os << "WorkstationDisplay\n";
    }

    // if the current object is the last Workstation in the assembly line this query inserts: ITEM_NAME
    //  --> End of Line.
    // in either case, the message is terminated with \n

    // Workstation& operator+=(CustomerOrder&& newOrder) – moves the CustomerOrder referenced in parameter
    //   newOrder to the back of the queue.
    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_front(newOrder);
        return *this;
    }

}