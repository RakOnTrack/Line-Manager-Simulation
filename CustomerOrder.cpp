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
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{

    size_t m_widthField{};
    CustomerOrder::CustomerOrder(const std::string rec)
    {
        Utilities util; // to locally use its functions
        size_t pos = 0u;
        bool dummy{};         // for calling util.extractToken
        bool more = true;     // to know if the while loop should continue
        size_t savePos = pos; // for going back to saved position
                              // name
        m_name = util.extractToken(rec, pos, dummy);
        // product
        m_product = util.extractToken(rec, pos, dummy);
        // find how many items there are, to know how much space to allocate to items pointer.
        savePos = pos;
        while (more)
        {
            util.extractToken(rec, pos, more);
            ++m_cntItem;
        }
        m_lstItem = new Item *[m_cntItem];
        // go back to saved position, read the items again, and save them to allocated pointer space.
        m_cntItem = 0;
        more = true;
        pos = savePos;
        while (more)
        {
            Item *token = new Item(util.extractToken(rec, pos, more));
            m_lstItem[m_cntItem++] = token;
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&co) noexcept
    {
        *this = move(co); // call move assignment operator
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&co) noexcept
    {
        if (this != &co)
        {
            for (size_t i = 0; i < m_cntItem; i++) // remove each item
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            // copy name, product, listItem pointer, item count.
            this->m_name = co.m_name;
            this->m_product = co.m_product;

            m_lstItem = co.m_lstItem;
            m_cntItem = co.m_cntItem;

            // set source to blank.
            co.m_name = "";
            co.m_product = "";
            co.m_cntItem = 0;
            co.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
    bool CustomerOrder::isOrderFilled() const
    {
        bool returnValue = true;

        for (size_t i = 0; i < m_cntItem && returnValue; ++i)
        {
            if (!m_lstItem[i]->m_isFilled) // check if theres an item in the order that isnt filled.
            {
                returnValue = false;
            }
        }
        return returnValue;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        bool returnValue = true;

        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) // check if the item names match, and if the item isnt already filled.
            {
                returnValue = false;
            }
        }
        return returnValue;
    }
    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        bool found = 0;
        for (size_t i = 0; i < m_cntItem && !found; ++i)
        {
            if (station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() > 0) // check if the names match, and the quantiy is greater than zero.
            {
                found = 1;
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                station.updateQuantity();
            }
        }
    }
    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << endl;
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            os << "[000000] " << std::setw(32) << left << m_lstItem[i]->m_itemName;

            if (m_lstItem[i]->m_isFilled)
            {
                os << " - FILLED " << endl;
            }
            else
            {
                os << " - TO BE FILLED" << endl;
            }
        }
    }

}