// Name: Eric Rak
// Seneca Student ID: 180211211
// Seneca email: erak@myseneca.ca
// Date of completion: Mar 25th 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include <string>

#include <iomanip>
#include <cstring>
#include <string>
#include <cctype>
#include "Station.h"
namespace sdds
{

    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string &src) : m_itemName(src){};
    };

    class CustomerOrder
    {

        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item **m_lstItem{};

        static size_t m_widthField;

    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string rec);
        CustomerOrder(CustomerOrder &co) { throw "error"; };
        CustomerOrder &operator=(CustomerOrder &co) = delete;
        CustomerOrder(CustomerOrder &&co) noexcept;

        CustomerOrder &operator=(CustomerOrder &&co) noexcept;

        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;
    };
}

#endif